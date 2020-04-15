#include "../includes/parsing.h"

int		is_esc(char *str, int i)
{
	int nb;

	nb = 0;
	if (str[i])
	{
		if (i > 0 && str[i - 1] == '\\')
		{
			i--;
			while (str[i] == '\\')
			{
				i--;
				nb++;
			}
			if (nb % 2)
				return (1);
		}
	}
	return (0);
}

void	ft_exit_rd(char* msg, char symbol)
{
	int		i;
	char*	tmp;

	i = ft_strlen(msg);
	if (!(tmp = malloc(i + 3)))
		ft_exit("malloc failed\n", 1);
	i = 0;
	while (msg[i])
	{
		tmp[i] = msg[i];
		i++;
	}
	tmp[i++] = symbol;
	tmp[i++] = '\'';
	tmp[i++] = '\n';
	tmp[i] = '\0';
	ft_exit(tmp, 1);
}

void	ft_exit(char* msg, int status)
{
	int	len;

	len = ft_strlen(msg);
	write(1, msg, len);
	ft_exit_2(NULL, status);
}

void	prompt()
{
	write(1, "$ ", 2);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
