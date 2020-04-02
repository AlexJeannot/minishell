#include "minishell.h"

char *map;

static int		dollar_to_del_len(char* str, int i)
{
	int len;

	len = 0;
	while (str[i] != ' ' && str[i])
	{
		i++;
		len++;
	}
	return (len);
}

static char*	remove_dollar(char* str, int i)
{
	int		len;
	char*	res;
	int		j;

	map = map_quote(str, 0);
	len = dollar_to_del_len(str, i);
	if (!(res = malloc(ft_strlen(str) - len + 1)))
		ft_exit(1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			while (str[i] != ' ' && str[i])
				i++;
		res[j++] = str[i++];
	}
	res[j] = '\0';
	free(map);
	printf("res[%s]\n", res);
	return (res);
}

char*	clear_echo_bad_env(char* str)
{
	char*	res;
	int		i;

	i = 0;
	res = NULL;
	if (!ft_strcmp(lst->cmd, "echo"))
	{
		map = map_quote(str, 0);
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] != ' ' 
				&& str[i + 1] && map[i] != '1' && !is_esc(lst->cmd, i)
				&& !is_env(str, i))
			{
				res = remove_dollar(str, i);
			}
			i++;
		}
	}
	if (res)
		return (res);
	return (str);
}
