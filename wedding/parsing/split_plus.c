#include "../includes/parsing.h"

char*	map;

static int	sep(char c, int i, char charset)
{
	if (c == charset && map[i] == '0')
		return (1);
	return (0);
}

static int	set_sep(char *str, char charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (sep(str[i], i, charset))
			count++;
		i++;
	}
	return (count + 1);
}

static char	*finder(char *str, int i, char charset)
{
	char	*part;
	int		j;
	int		len;

	while (str[i] == ' ')
		i++;
	len = 0;
	j = i;
	while (str[i] && !sep(str[i], i, charset))
	{
		len++;
		i++;
	}
	if (!(part = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	i = j;
	j = 0;
	while (len)
	{
		part[j++] = str[i++];
		len--;
	}
	part[j] = '\0';
	return (part);
}

char		**split_plus(char *str, char charset)
{
	int		i;
	int		j;
	char	**tab;

	map = map_quote(str, 0);
	i = set_sep(str, charset);
	if (!(tab = malloc((i + 1) * sizeof(char*))))
		ft_error('\0', "Malloc", NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] && !sep(str[i], i, charset))
		{
			tab[j++] = finder(str, i, charset);
			while (str[i] && !sep(str[i], i, charset))
				i++;
		}
		i++;
	}
	tab[j] = NULL;
	free_str(&map);
	return (tab);
}
