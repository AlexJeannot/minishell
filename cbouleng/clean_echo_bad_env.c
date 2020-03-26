#include "minishell.h"

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
	return (res);
}

char*	clean_echo_bad_env(char* str)
{
	char*	res;
	int		i;

	i = 0;
	if (!ft_strcmp(lst->cmd, "echo"))
	{
		map = map_quote(str);
		while (str[i])
		{
			if (str[i] == '$' && map[i] != '1' && !is_esc(lst->cmd, i)
				&& !is_env(str, i))
				res = remove_dollar(str, i);
			i++;
		}
	}
	return (res);
}
