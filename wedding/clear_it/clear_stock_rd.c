#include "../includes/parsing.h"

char* map;

int		is_rd(char* str, int i)
{
	if (!is_esc(str, i) && map[i] == '0')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (1);
		if (str[i] == '>' && str[i - 1] != '>')
			return (1);
		if (str[i] == '<')
			return (1);
	}
	return (0);
}

char* clear_stock_rd(char* str)
{
	int	i;

	i = 0;
	map = map_quote(str, 0);
	while (str[i])
	{
		if (is_rd(str, i))
		{
			str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			while (is_name(str,i))
				str[i++] = ' ';
		}
		if (!is_rd(str, i))
			i++;
	}
	return (str);
}
