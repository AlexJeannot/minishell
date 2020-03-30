#include "minishell.h"

int		bs_in_row(char* str, int* p_i)
{
	int	nb;

	nb = 0;
	while (str[*p_i] == '\\')
	{
		nb++;
		(*p_i)++;
	}
	if (!(nb % 2)
		return (nb / 2);
	return (nb / 2 + 1);
}

int		nb_del_case(char* str, int* p_i)
{
	if (str[*(p_i + 1)] == '|')
		return (0);
	if (str[*(p_i + 1)] == '\\')
		return (bs_in_row(str, p_i));
	return (1);
}

int		nb_to_del(char* str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			nb = nb_del_case(str, &i);
		sum += nb;
		nb = 0;
		i++;
	}
	return (sum);
}

int		print_case(char* str, int* p_i)
{
	if (str[*p_i] == '\\')
	{
		if (str[*(p_i + 1)] == '|')
			return (1);
		if (str[*(p_i + 1)] == '\\')
			
	}
	return (1);
}

void	clear_it(char* str)
{
	int		nb;
	char*	res;
	int		i;

	i = 0;
	nb = nb_to_del(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit(1);
	while (str[i])
	{
			if (print_case(str, &i))

}

void	clear_backslash(void)
{
	int	i;

	i = 0;
	clear_it(lst->cmd);
	while (lst->arg[i])
		clear_it(lst->arg[i++]);
}
