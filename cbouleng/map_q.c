#include "minishell.h"

int		map_double_quote(char* str, int i)
{
	map_d[i++] = '2';
	while (str[i] != '"' && !is_escaped(str, i, '"'))
		map_d[i++] = '2';
	map_d[i] = '2';
	return (i);
}

int		map_simple_quote(char* str, int i)
{
	map_s[i++] = '1';
	while (str[i] != '\'' && !is_escaped(str, i, '\''))
		map_s[i++] = '1';
	map_s[i] = '1';
	return (i);
}

void	map_q(char *str)
{
	int i;

	if (!(map_s = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	if (!(map_d = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_escaped(str, i))
			i = map_double_quote(str, i);
		else if (str[i] == '\'' && !is_escaped(str, i))
			i = map_simple_quote(str, i);
		else
		{
			map_s[i] = '0';
			map_d[i] = '0';
		}
		i++;
	}
	map_s[i] = '\0';
	map_d[i] = '\0';
}
