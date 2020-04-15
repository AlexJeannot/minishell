#include "../includes/parsing.h"

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
		ft_error('\0', "Malloc", NULL);
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

t_value		new_value(int i, int j)
{
	t_value	v;
	int		len;

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
		ft_error('\0', "Malloc", NULL);
	return (v);
}
