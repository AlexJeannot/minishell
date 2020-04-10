#include "minishell.h"

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
		ft_exit("malloc failed", 1);
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
			ft_exit("malloc failed", 1);
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

t_cont	get_redir(char* str)
{
	t_cont cont;

	map = map_quote(str, 0);
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
	return (cont);
}
