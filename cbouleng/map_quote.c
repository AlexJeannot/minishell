#include "minishell.h"

static void	check_conform(void)
{
	int end;

	end = ft_strlen(map_s);
	if (map_s[end - 1] == '1' && map_s[end - 2] == '0')
		ft_exit(1);
	if (map_d[end - 1] == '2' && map_d[end - 2] == '0')
		ft_exit(1);
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
		if (str[i] == '"' && !is_esc(str, i) && flag_s > 0)
			flag_d *= -1;
		if (str[i] == '\'' && !is_esc(str, i) && flag_d > 0)
			flag_s *= -1;
		if (flag_d < 0)
			map_d[i] = '2';
		if (flag_s < 0)
			map_s[i] = '1';
		if (flag_d > 0)
			map_d[i] = '0';
		if (flag_s > 0)
			map_s[i] = '0';
		i++;
	}
	map_s[i] = '\0';
	map_d[i] = '\0';
}

void	map_quote(char *str)
{
	if (!(map_s = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	if (!(map_d = malloc(ft_strlen(str) + 1)))
		ft_exit(1);
	mapping(str);
	check_conform();
	printf("\nmap_s:[%s]\n", map_s);
	printf("map_d:[%s]\n", map_d);
}
