#include "minishell.h"

int		find_rdc(char* str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && !is_esc(str, i))
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
		if ((str[i] == '>' && !is_esc(str, i)) || 
			(str[i] == '>' && str[i + 1] == '>' && !is_esc(str, i)))
			nb++;
		i++;
	}
	return (nb);
}

char*	get_filename(char* str, int i)
{
	char*	name;
	int		len;

	
	if (!(name = malloc(len + 1)))
		ft_exit("malloc failed", 1);

}

char**	get_rdc_filetab(char* str)
{
	char**	tab;
	int		nb;

	if (find_rdc(str))
	{
		nb = count_rdc(str);
		if (!(tab = malloc(sizeof(char*) * nb + 1)))
			ft_exit("malloc failed", 1);
		while (i < nb)
		{
			tab[i] = get_filename(str, i);
			i++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}

t_cont	get_redir(char* str)
{
	t_cont cont;

	cont.rdc_filetab = get_rdc_filetab(str);
	cont.rdo_filetab = get_rdo_filetab(str);
}
