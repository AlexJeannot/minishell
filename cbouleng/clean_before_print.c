#include "minishell.h"

static int	nb_del_quote(char* str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_esc(str, i) && map_d[i] == '2')
			nb++;
		if (str[i] == '\'' && !is_esc(str, i) && map_s[i] == '1')
			nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char* str, int i)
{
	if (str[i] == '"' && !is_esc(str, i) && map_d[i] == '2')
		return (0);
	if (str[i] == '\'' && !is_esc(str, i) && map_s[i] == '1')
		return (0);
	return (1);
}

static char*	clean_quote(char* str)
{
	char*	res;
	int		nb;
	int		j;
	int		k;

	map_quote(str);
	nb = nb_del_quote(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit(1);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (to_print(str, j))
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	return (res);
}

void	clean_before_print(void)
{
	int	i;

	i = 0;
	lst->cmd = clean_quote(lst->cmd);
	while (lst->arg[i])
	{
		lst->arg[i] = clean_quote(lst->arg[i]);
		i++;
	}
}
