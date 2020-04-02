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
		if (map[i + 1] == '2' && str[i] == '\\' && str[i + 1] == '"')
			nb++;
	//	if (str[i] == '\\' && is_esc(str, i))
	//		nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char* str, int i)
{
	if (!map[i + 1] && str[i] == '"')
		return (0);
	if (map[i + 1] && str[i] == '"' && str[i - 1] == '\\')
		return (1);
	if (map[i] == '2' && str[i + 2] && str[i] == '\\' && str[i + 1] == '"')
		return (0);
	if (map[i] == '4' || map[i] == '3')
		return (0);
	return (1);
}

static char*	clear_quote(char* str)
{
	char*	res;
	int		nb;
	int		j;
	int		k;

	map = map_quote(str, 0);
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
	free(map);
	return (res);
}

void	clear_before_print(void)
{
	int	i;

	i = 0;
	clear_backslash();
	lst->cmd = clear_quote(lst->cmd);
	while (lst->arg[i])
	{
		lst->arg[i] = clear_echo_bad_env(lst->arg[i]);
		lst->arg[i] = clear_quote(lst->arg[i]);
		i++;
	}
}
