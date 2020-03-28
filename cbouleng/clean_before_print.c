#include "minishell.h"

char*	map;

static int	nb_del_quote(char* str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (map[i] == '4' || map[i] == '3')
			nb++;
		i++;
	}
	return (nb);
}

static int	to_print(int i)
{
	if (map[i] == '4' || map[i] == '3')
		return (0);
	return (1);
}

static char*	clean_quote(char* str)
{
	char*	res;
	int		nb;
	int		j;
	int		k;

	map = map_quote(str);
	nb = nb_del_quote(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit(1);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (to_print(j))
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	return (res);
}

void	clean_before_print(void)
{
	int	i;
//	int	arg_len;

	i = 0;
	lst->cmd = clean_quote(lst->cmd);
	lst->cmd = clean_backslash(lst->cmd);
//	arg_len = ft_tablen(lst->arg);
	while (lst->arg[i])
	{
		lst->arg[i] = clean_quote(lst->arg[i]);
		lst->arg[i] = clean_backslash(lst->arg[i]);
//		lst->arg[i] = clean_echo_bad_env(lst->arg[i]);
		i++;
	}
//	defrag_arg(arg_len);
}
