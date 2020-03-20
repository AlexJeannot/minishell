#include "minishell.h"

int		is_path(char *str)
{
	char	*tmp;
	int		i;

	tmp = "path";
	i = 0;
	while (tmp[i] && str[i] == tmp[i])
		i++;
	if (str[i] != tmp[i])
		return (0);
	return (1);
}

char*	get_env_name_2check(char *str, int j)
{
	int		len;
	int		i;
	char	*tmp;

	j++;
	len = j;
	i = 0;
	while (str[j] && str[j] != ' ')
		j++;
	if (!(tmp = malloc(j - len + 1)))
		ft_exit(1);
	while (len < j && ((str[len] >= '0' && str[len] <= '9') ||
	(str[len] >= 'a' && str[len] <= 'z') || (str[len] >= 'A' &&
	str[len] <= 'Z')))
		tmp[i++] = str[len++];
	tmp[i] = '\0';
	return (tmp);
}

int		ft_envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && !s2[i])
		return (1);
	return (0);
}

int		is_env(char *str, int j)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_env_name_2check(str, j);
	if (is_path(tmp))
		return (2);
	while (global_env[i])
	{
		if (ft_envcmp(global_env[i], tmp))
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

t_value		new_value(int i, int j, int ret)
{
	t_value	v;
	int		len;

	if (ret == 2)
		v.name = "PATH";
	else
		v.name = get_env_name_2check(lst->arg[i], j);
	i = 0;
	while (global_env[i] && !ft_envcmp(global_env[i], v.name))
		i++;
	j = 0;
	while (global_env[i][j] != '=')
		j++;
	len = 0;
	v.i = i;
	v.j = j + 1;
	while (global_env[i][++j])
		len++;
	if (!(v.value = malloc(len + 1)))
		ft_exit(1);
	return (v);
}
