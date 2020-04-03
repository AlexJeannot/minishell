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
		else if (str[i] == '\\' && str[i + 1] == '"')
			nb++;
	//	else if (str[i] == '\\' && is_esc(str, i))
	//		nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char* str, int i)
{
	if (str[i] == '"' && !str[i + 1] && map[i] == '2')
		return (0);
	if (str[i] == '\\' && !is_esc(str, i) && (str[i + 1] == '"' 
		|| str[i + 1] == '\'') && map[i] == '0')
		return (0);
	if (str[i] == '\\' && str[i + 1] == '"' && str[i + 2])
		return (0);
	if ((map[i] == '4' || map[i] == '3') && str[i - 1] != '\\')
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
	//printf("quote[%d][%s]\n", nb, str);
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
	//printf("cl_k[%d]\n", k);
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
