#include "minishell.h"

char* map;

int		is_rdc(char* str, int i)
{
	if (str[i] == '>' && !is_esc(str, i) && map[i] == '0')
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && !is_esc(str, i) && map[i] == '0')
		return (2);
	return (0);
}

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
		if (map[i] == '0' && !is_esc(str, i) && (str[i] == '>' || 
			(str[i] == '>' && str[i + 1] == '>')))
			nb++;
		i++;
	}
	return (nb);
}

int		is_name(char* str, int i)
{
	if (str[i] > 'a' && str[i] < 'z')
		return (1);
	if (str[i] > 'A' && str[i] < 'Z')
		return (1);
	if (str[i] > '0' && str[i] < 'z')
		return (1);
	if (str[i] == '_')
		return (1);
	if (str[i] == '.')
		return (1);
	if (str[i] == '-')
		return (1);
	return (0);
}

char*	get_name(char* str, int i)
{
	char*	name;
	int		len;

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

char*	get_rdc_name(char* str, int i)
{
	char*	name;
	int		nb;
	int		y;
	
	y = 0;
	nb = 0;
	while (str[y])
	{
		if (is_rdc(str, y))
			nb++;
		if (nb == i)
			name = get_name(str, y + 1);
		y++;
	}
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
		i = 0;
		while (i < nb)
		{
			tab[i] = get_rdc_name(str, i);
			i++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}

char*	get_last(char** tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (tab[i]);
}

int		get_rdc_type(char* str)
{
	int	i;

	i = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '>' && str[i - 1] == '>')
			return (2);
		if (str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

t_cont	get_redir(char* str)
{
	t_cont cont;
	
	map = map_quote(str, 0);
	cont.rdc_filetab = get_rdc_filetab(str);
//	cont.rdo_filetab = get_rdo_filetab(str);
	cont.rdc_filename = get_last(cont.rdc_filetab);
//	cont.rdo_filename = get_last(cont.rdo_filetab);
	cont.rdc_type = get_rdc_type(str);
//	cont.rdo_type = get_rdo_type(str);
	return (cont);
}
