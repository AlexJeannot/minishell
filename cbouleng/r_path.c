#include "minishell.h"


char*
	get_lil_path_value(int i, int j)
{
	char	*value;
	int		len;
	int		k;

	len = 0;
	while (global_env[y][k])
	{
		if (global_env[y][k] == ':')
			value[len] = ' ';
		else
			value[len] = global_env[y][k];
		len++;
		k++;
	}
	value[len] = '\0';
	return (value);
}

char*
	get_lil_path_value(int i, int j)
{
	char	*value;
	int		len;
	int		k;

	y = 0;
	while (global_env[y] && !ft_envcmp(global_env[y], "PATH"))
		y++;
	i = 0;
	while (global_env[y][i] != '=')
		i++;
	i++;
	k = i;
	len = 0;
	while (global_env[y][i])
	{
		len++;
		i++;
	}
	if (!(value = malloc(len + 1)))
		ft_exit(1);
	len = 0;
	while (global_env[y][k])
	{
		if (global_env[y][k] == ':')
			value[len] = ' ';
		else
			value[len] = global_env[y][k];
		len++;
		k++;
	}
	value[len] = '\0';
	return (value);
}
