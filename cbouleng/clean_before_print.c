#include "minishell.h"

static int	nb_del_quote(char* str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_esc(str, i) && map_d[i] == '2')
			nb++;
		if (str[i] == '\'' && !is_esc(str, i) && map_s[i] == '1')
			nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char* str, int i)
{
	if (str[i] == '"' && !is_esc(str, i) && map_d[i] == '2')
		return (0);
	if (str[i] == '\'' && !is_esc(str, i) && map_s[i] == '1')
		return (0);
	return (1);
}

static char*	clean_quote(char* str)
{
	char*	res;
	int		nb;
	int		j;
	int		k;

	map_quote(str);
	nb = nb_del_quote(str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_exit(1);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (to_print(str, j))
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	return (res);
}

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

static char*	clean_backslash(char* str)
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

void	clean_before_print(void)
{
	int	i;

	i = 0;
	lst->cmd = clean_quote(lst->cmd);
	lst->cmd = clean_backslash(lst->cmd);
	while (lst->arg[i])
	{
		lst->arg[i] = clean_quote(lst->arg[i]);
		lst->arg[i] = clean_backslash(lst->arg[i]);
		i++;
	}
//	defrag_arg();
}
