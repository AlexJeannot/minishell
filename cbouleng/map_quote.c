#include "minishell.h"

char*	map;

static void mapping(char *str)
{
	int	flag_d;
	int	flag_s;
	int	i;
	
	flag_d = 1;
	flag_s = 1;
	i = 0;
	while (str[i])
	{
		if (flag_d > 0)
			map[i] = '0';
		if (flag_s > 0)
			map[i] = '0';
		if (flag_d < 0)
			map[i] = '2';
		if (flag_s < 0)
			map[i] = '1';
		if (str[i] == '"' && !is_esc(str, i) && flag_s > 0)
		{
			flag_d *= -1;
			map[i] = '4';
		}
		if (str[i] == '\'' && flag_d > 0)
		{
			flag_s *= -1;
			map[i] = '3';
		}
		i++;
	}
	map[i] = '\0';
	//printf("map[%s]\n", map);
}

static void mapping_2(char *str)
{
	int	flag_d;
	int	flag_s;
	int	i;
	
	flag_d = 1;
	flag_s = 1;
	i = 0;
	while (str[i])
	{
		if (flag_d > 0)
			map[i] = '0';
		if (flag_s > 0)
			map[i] = '0';
		if (flag_d < 0)
			map[i] = '2';
		if (flag_s < 0)
			map[i] = '1';
		if (str[i] == '"' && str[i - 1] != '\\' && flag_s > 0)
		{
			flag_d *= -1;
			map[i] = '4';
		}
		if (str[i] == '\'' && flag_d > 0)
		{
			flag_s *= -1;
			map[i] = '3';
		}
		i++;
	}
	map[i] = '\0';
//	printf("map2[%s]\n", map);
}

char*	map_quote(char *str, int pos)
{
	if (!(map = malloc(ft_strlen(str) + 1)))
		ft_exit("malloc failed", 1);
	if (pos)
		mapping_2(str);
	else
		mapping(str);
	return (map);
}
