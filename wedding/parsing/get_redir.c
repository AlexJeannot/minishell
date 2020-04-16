#include "../includes/parsing.h"

char* map;

int		find_rdc(char* str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_esc(str, i) && map[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int		count_rdc(char* str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '>' && str[i + 1] == '>')
				nb++;
			else if (str[i] == '>' && str[i - 1] != '>')
				nb++;
		}
		i++;
	}
	return (nb);
}

int		is_name(char* str, int i)
{
	if (str[i] >= 'a' && str[i] <= 'z')
		return (1);
	if (str[i] >= 'A' && str[i] <= 'Z')
		return (1);
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	if (str[i] == '_')
		return (1);
	if (str[i] == '.')
		return (1);
	if (str[i] == '-')
		return (1);
	return (0);
}

char*	get_name(char* str, int i, int ret)
{
	char*	name;
	int		len;

	if (ret == 2)
		i++;
	while (str[i] == ' ')
		i++;
	len = i;
	while (is_name(str, i))
		i++;
	len = i - len;
	if (!(name = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	i = i - len;
	len = 0;
	while (is_name(str, i))
		name[len++] = str[i++];
	name[len] = '\0';
	return (name);
}

int		is_rdc(char* str, int i)
{
	if (!is_esc(str, i) && map[i] == '0')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (2);
		if (str[i] == '>' && str[i - 1] != '>')
			return (1);
	}
	return (0);
}

char*	get_rdc_name(char* str, int i)
{
	char*	name;
	int		nb;
	int		y;
	int		ret;

	y = 0;
	nb = 0;
	name = NULL;
	while (nb != i && str[y])
	{
		if ((ret = is_rdc(str, y)))
			nb++;
		y++;
	}
	if (nb == i)
		name = get_name(str, y, ret);
	return (name);
}

char**	get_rdc_filetab(char* str)
{
	char**	tab;
	int		nb;
	int		i;

	if (find_rdc(str))
	{
		nb = count_rdc(str);
		if (!(tab = malloc(sizeof(char*) * nb + 1)))
		ft_error('\0', "Malloc", NULL);
		i = 1;
		while (i <= nb)
		{
			tab[i - 1] = get_rdc_name(str, i);
			i++;
		}
		tab[i - 1] = NULL;
		return (tab);
	}
	return (NULL);
}

char*	get_last(char** tab)
{
	int	i;


	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	return (tab[i - 1]);
}


int		get_rdc_type(char* str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == '>' && str[i - 1] == '>')
			return (2);
		if (str[i] == '>')
			return (1);
		i--;
	}
	return (0);
}


t_cont	init_cont(void)
{
	t_cont cont;

	cont.rdc_type = 0;
	cont.rdc_filetab = NULL;
	cont.rdc_filename = NULL;
	cont.rdo_type = 0;
	cont.rdo_filetab = NULL;
	cont.rdo_filename = NULL;
	return (cont);
}


/* DEBUT AJOUT FONCTIONS INDEX RDC RDO -> ALEX */

int *create_index_array(char *str, char *type)
{
	int count;
	int *index_array;

	count = 0;
	if (ft_strcmp("rdc", type) == 0)
		count = count_rdc(str);
	else if (ft_strcmp("rdo", type) == 0)
		count = count_rdo(str);
	if (!(index_array = (int *)malloc(sizeof(int) * (count + 1))))
		ft_error('\0', "Malloc", NULL);
	return (index_array);
}

void get_rd_index(char *str, int *rdc_index, int *rdo_index)
{
	int i;
	int index;
	int rdc_add;
	int rdo_add;

	i  = 0;
	index = 0;
	rdc_add = 0;
	rdo_add = 0;
	while (str[i])
	{
		/* IF RDC*/
		if (str[i] == '>' && !is_esc(str, i) && map[i] == '0')
		{
			rdc_index[rdc_add] = index;
			if (str[i + 1] && str[i + 1] == '>')
				i++;
			index++;
			rdc_add++;
		}

		/* IF RDO*/
		if (str[i] == '<' && !is_esc(str, i) && map[i] == '0')
		{
			rdo_index[rdo_add] = index;
			index++;
			rdo_add++;
		}
		i++;
	}
	rdc_index[rdc_add] = -1;
	rdo_index[rdo_add] = -1;
}

/* FIN AJOUT FONCTIONS INDEX RDC RDO -> ALEX */


t_cont	get_redir(char* str)
{
	int *rdc_index; // Ajout index des rdc
	int *rdo_index;	// Ajout index des rdo
	t_cont cont;

	map = map_quote(str, 0);

	rdc_index = create_index_array(str, "rdc"); // Creation de l'array de int pour les index rdc
	rdo_index = create_index_array(str, "rdo"); // Create dion l'array de int pour les index rdo
	get_rd_index(str, rdc_index, rdo_index); // Remplissage des index rdc et rdo

	cont = init_cont();
	if (find_rdc(str))
	{
		cont.rdc_filetab = get_rdc_filetab(str);
		cont.rdc_filename = get_last(cont.rdc_filetab);
		cont.rdc_type = get_rdc_type(str);
	}
	if (find_rdo(str))
	{
		cont.rdo_filetab = get_rdo_filetab(str);
		cont.rdo_filename = get_last(cont.rdo_filetab);
		cont.rdo_type = 1;
	}
	cont.rdc_index = rdc_index; // Ajout de l'index rdc dans la structure cont
	cont.rdo_index = rdo_index; // Ajout de l'index rdo dans la structure cont
	free_str(&map);
	return (cont);
}
