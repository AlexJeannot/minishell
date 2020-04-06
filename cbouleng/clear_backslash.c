#include "minishell.h"

char* map;

//int		bs_in_row(char* str, int* p_i)
//{
//	int	nb;
//
//	nb = 0;
//	while (str[*p_i] == '\\')
//	{
//		nb++;
//		(*p_i)++;
//	}
//	printf("[[%c]%d]\n", str[*p_i], nb);
//	if (str[*p_i] == '"' || str[*p_i] == '\'')
//		return (0);
//	if (!(nb % 2))
//		nb /= 2;
////		return (nb / 2);
//	else
//		nb = nb / 2 + 1;
////	return (nb / 2 + 1);
//	printf("nb_del[%d]\n", nb);
//	return (nb);
//}

//int		nb_del_case(char* str, int* p_i)
//{
//	if (str[(*p_i + 1)] == '|' && map[*p_i] == '1')
//	{
//		printf("1[%c]\n", str[(*p_i + 1)]);
//		return (0);
//	}
//	if (map[*p_i] == '0' && (str[(*p_i + 1)] == '"' 
//		|| str[(*p_i + 1)] == '\''))
//	{
//		printf("2[%c]\n", str[(*p_i + 1)]);
//		return (0);
//	}
//	if (str[(*p_i + 1)] == '\\' && !is_esc(str, *p_i + 1))
//	{
//		printf("3[%c]\n", str[(*p_i + 1)]);
//		return (0);
//	}
////	if (str[(*p_i + 1)] == '\\')
////		return (bs_in_row(str, p_i));
//	if (str[(*p_i + 1)] == ' ')
//	{
//		printf("4[%c]\n", str[(*p_i + 1)]);
//		return (0);
//	}
//	printf("out[%c]\n", str[(*p_i + 1)]);
//	return (0);
//}

//int		quote_case(char* str, int i)
//{
//	int	nb;
//
//	nb = 0;
//	while (str[i + 1] == '\\')
//	{
//		i++;
//		nb++;
//	}
//	if (str[i] == '"' || str[i] == '\'')
//		return (nb);
//	return (0);
//}

int		nb_del_case(char* str, int* p_i)
{
	if (str[*p_i] == '\\' && map[*p_i] != '1')
	{
		if (str[(*p_i + 1)] == '"' || str[(*p_i + 1)] == '\'')
			return (0);
		if (str[(*p_i + 1)] == '|' && map[*p_i] == '2')
			return (0);
		if (str[(*p_i + 1)] == ' ')
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

int		esc_case(char* str, int i)
{
	while (str[i] == '\\')
		i++;
	if (str[i] == '"' && map[i] == '4')
		return (1);
	return (0);
}

//int		print_case(char* str, int* p_i)
//{
//	if (str[*p_i] == '\\' && map[*p_i] != '1')
//	{
//		//		if (esc_case(str, *p_i))
//		//			return (1);
//		//		if (str[(*p_i + 1)] == '\\')
//		//		{
//		//			(*p_i)++;
//		//			return (1);
//		//		}
//		//		if (str[(*p_i + 1)] == '|')
//		if (!is_esc(str, *p_i) && map[*p_i] == '0')
//			return (0);
//		return (1);
//	}
//	return (1);
//}

char*	clear_it(char* str)
{
	int		nb;
	char*	res;
	int		i;

	i = 0;
	map = map_quote(str, 0);
	nb = nb_to_del(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit("Malloc failed", 1);
	nb = 0;
	while (str[i])
	{
		if (!nb_del_case(str, &i)) //print_case(str, &i))
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
