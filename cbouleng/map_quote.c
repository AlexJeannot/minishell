#include "minishell.h"

char*	map;

static void	check_simple(char* str)
{
	int i;
	
	i = 0;
	while (map[i])
	{
		if (map[i] == '3')
		{
			i++;
			while (map[i] == '1')
				i++;
			if (map[i] != '3' || str[i] != '\'')
				ft_exit(1);
		}
		i++;
	}
}

static void	check_double(char* str)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '4')
		{
			i++;
			while (map[i] == '2')
				i++;
			if (map[i] != '4' || str[i] != '"')
				ft_exit(1);
		}
		i++;
	}
}

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
		if (str[i] == '\'' && !is_esc(str, i) && flag_d > 0)
		{
			flag_s *= -1;
			map[i] = '3';
		}
		i++;
	}
	map[i] = '\0';
	printf("map[%s]\n", map);
}

char*	map_quote(char *str)
{
	if (!(map = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	mapping(str);
	check_simple(str);
	check_double(str);
	return (map);
}
