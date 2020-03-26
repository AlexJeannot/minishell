#include "minishell.h"

static int		nb_del_backslash(char* str)
{
	int	i;
	int	nb;
	int	sum;

	i = 0;
	sum = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			while (str[i] == '\\')
			{
				nb++;
				i++;
			}
			if (!(nb % 2))
				nb /= 2;
			else
				nb = nb / 2 + 1;
		}
		sum += nb;
		nb = 0;
		i++;
	}
	return (sum);
}

static int	print_it(char* str, int i)
{
	int nb;

	nb = 0;
	if (str[i] == '\\')
	{
		while (str[i--] == '\\')
			nb++;
		return (nb / 2);
	}
	return (0);
}

char*	clean_backslash(char* str)
{
	char*	res;
	int		nb;
	int		i;
	int		j;
	int		ret;

	ret = 0;
	nb = nb_del_backslash(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit(1);
	i = ft_strlen(str);
	j = i - nb;
	res[j--] = '\0';
	i--;
	while (i >= 0)
	{
		if (str[i] == '\\')
		{
			ret = print_it(str, i);
			while (ret)
			{
				res[j--] = '\\';
				i--;
				ret--;
			}
		}
		else
			res[j--] = str[i];
		i--;
	}
	return (res);
}
