#include "../includes/minishell.h"

char* map;

int		is_spe_carac(char* str, int i)
{
	if (str[i] == 36)
		return (0);
	if (str[i] >= 32 && str[i] <= 47)
		return (1);
	if (str[i] >= 58 && str[i] <= 64)
		return (1);
	if (str[i] == 91 || (str[i] >= 93 && str[i] < 96))
		return (1);
	if (str[i] >= 123 && str[i] <= 126)
		return (1);
	return (0);
}

int		nb_del_case(char* str, int* p_i)
{
	if (str[*p_i] == '\\' && map[*p_i] != '1')
	{
		if (str[(*p_i + 1)] == '"' || str[(*p_i + 1)] == '\'')
			return (0);
		if (is_spe_carac(str, *p_i + 1) && map[*p_i] == '2')
			return (0);
		if (!is_esc(str, *p_i))
			return (1);
		return (0);
	}
	return (0);
}

int		nb_to_del(char* str)
{
	int	i;
	int	sum;
	int	nb;

	i = 0;
	sum = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\\' && map[i] != '1')
			nb = nb_del_case(str, &i);
		sum += nb;
		nb = 0;
		i++;
	}
	return (sum);
}

char*	clear_it(char* str)
{
	int		nb;
	char*	res;
	int		i;

	i = 0;
	map = map_quote(str, 0);
	nb = nb_to_del(str);
//	printf("bs[%s][%d]\n", str, nb);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit("Malloc failed", 1);
	nb = 0;
	while (str[i])
	{
		if (!nb_del_case(str, &i))
			res[nb++] = str[i];
		i++;
	}
	res[nb] = '\0';
//	printf("res_bs[%s]\n", res);
	free(map);
	return (res);
}

void	clear_backslash(void)
{
	int	i;

	i = 0;
	lst->cmd = clear_it(lst->cmd);
	while (lst->arg[i])
	{
		lst->arg[i] = clear_it(lst->arg[i]);
		i++;
	}
}
