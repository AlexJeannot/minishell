#include "minishell.h"

static int		is_paired(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' && str[i])
			i++;
		if (str[i] == '"')
			return (1);
	}
	else
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		if (str[i] == '\'')
			return (1);
	}
	return (0);
}

static int		map_s_help(int i)
{
	if (map_s)
	{
		if (map_s[i] != '0')
			return (0);
	}
	return (1);
}

static int		map_d_help(int i)
{
	if (map_d)
	{
		if (map_d[i] != '0')
			return (0);
	}
	return (1);
}

void	map_double_quote(char *str)
{
	int 	i;

	i = ft_strlen(str);
	if (!(map_d = malloc(i + 1)))
		ft_exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !is_escaped(str, i) && is_paired(str, i)
			&& map_s_help(i))
		{
			map_d[i++] = '2';
			while (str[i] != '"' && !is_escaped(str, i))
				map_d[i++] = '2';
			map_d[i++] = '2';
		}
		else
			map_d[i++] = '0';
	}
	map_d[i] = '\0';
}

void	map_simple_quote(char *str)
{
	int 	i;

	i = ft_strlen(str);
	if (!(map_s = malloc(i + 1)))
		exit(1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !is_escaped(str, i) && is_paired(str, i)
			&& map_d_help(i))
		{
			map_s[i++] = '1';
			while (str[i] != '\'' && !is_escaped(str, i))
				map_s[i++] = '1';
			map_s[i++] = '1';
		}
		else
			map_s[i++] = '0';
	}
	map_s[i] = '\0';
}

void	fill_map(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!(map_s = malloc(len + 1)))
		ft_exit(1);
	if (!(map_d = malloc(len + 1)))
		ft_exit(1);
	while (str[i])
	{
		map_s[i] = '0';
		map_d[i++] = '0';
	}
	map_s[i] = '\0';
	map_d[i] = '\0';
	printf("\n[%s]\n[%s]\n", map_d, map_s);
}

void	map_quote(char *str)
{
	int i;

	i = 0;
	map_d = NULL;
	map_s = NULL;
	while ((str[i] != '"' && str[i] != '\'') && str[i])
		i++;
	if (str[i] == '"')
	{
		map_double_quote(str);
		map_simple_quote(str);
		printf("\n[%s]\n[%s]\n", map_d, map_s);
	}
	else if (str[i] == '\'')
	{
		map_simple_quote(str);
		map_double_quote(str);
		printf("\n[%s]\n[%s]\n", map_s, map_d);
	}
	else
		fill_map(str);
}
