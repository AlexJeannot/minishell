#include "minishell.h"

static void	check_simple(char* str)
{
	int i;
	
	i = 0;
	while (map_s[i])
	{
		if (map_s[i] == '3')
		{
			i++;
			while (map_s[i] == '1')
				i++;
			if (map_s[i] != '3' || str[i] != '\'')
				ft_exit(1);
		}
		i++;
	}
}

static void	check_double(char* str)
{
	int	i;

	i = 0;
	while (map_d[i])
	{
		if (map_d[i] == '4')
		{
			i++;
			while (map_d[i] == '2')
				i++;
			if (map_d[i] != '4' || str[i] != '"')
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
			map_d[i] = '0';
		if (flag_s > 0)
			map_s[i] = '0';
		if (flag_d < 0)
			map_d[i] = '2';
		if (flag_s < 0)
			map_s[i] = '1';
		if (str[i] == '"' && !is_esc(str, i) && flag_s > 0)
		{
			flag_d *= -1;
			map_d[i] = '4';
		}
		if (str[i] == '\'' && !is_esc(str, i) && flag_d > 0)
		{
			flag_s *= -1;
			map_s[i] = '3';
		}
		i++;
	}
	map_s[i] = '\0';
	map_d[i] = '\0';
	printf("\nmap_s[%s]\n", map_s);
	printf("map_d[%s]\n", map_d);
}

void	map_quote(char *str)
{
	if (map_s)
		free(map_s);
	if (map_d)
		free(map_d);
	if (!(map_s = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	if (!(map_d = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	mapping(str);
	check_simple(str);
	check_double(str);
}
