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

void	ft_error_rd(char* msg, char symbol)
{
	int		i;

	i = ft_strlen(msg);
	printf("ok\n");
	write(1, msg, i);
	if (!symbol)
		write(1, "newline", 7);
	else
		write(1, &symbol, 1);
	write (1, "'\n", 2);
	ft_exit(1);
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
