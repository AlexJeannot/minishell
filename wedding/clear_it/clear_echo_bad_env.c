#include "../includes/parsing.h"

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
		ft_exit("malloc failed", 1);
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
	return (res);
}

int		remove_it(char* str, int i)
{
	if (str[i] == '$' && !is_esc(str, i))
	{
		if (map[i] == '1')
			return (0);
		if (!str[i + 1])
			return (0);
		if (str[i + 1] > 31 && str[i + 1] < 47)
			return (0);
		if (str[i + 1] > 57 && str[i + 1] < 65)
			return (0);
		if (str[i + 1] > 90 && str[i + 1] < 97)
			return (0);
		if (str[i + 1] > 122 && str[i + 1] < 127)
			return (0);
		if (!is_env(str, i))
			return (1);
	}
	return (0);
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
			if (remove_it(str, i))
				res = remove_dollar(str, i);
			i++;
		}
	}
	free(map);
	if (res)
		return (res);
	return (str);
}
