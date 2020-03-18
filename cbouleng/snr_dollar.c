#include "minishell.h"

void quote_env()
{
	if (str[j - 1] == ''')
	{
		j++;
		while (str[j] && str[j] != ' ')
			j++;
	}
}

void double_quote_env()
{

}

char	*get_env_name_2check(char *str, int j)
{
	int		len;
	int		i;
	char	*tmp;

	len = j;
	i = 0;
	while (str[j] && str[j] != ' ')
		j++;
	if (!(tmp = malloc(j - len + 1)))
		ft_exit(1);
	while (len < j)
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

int		is_path(char *str)
{
	char	*tmp;
	int		i;

	tmp = "path";
	i = 0;
	while (str[i] == tmp[i])
		i++;
	if (!str[i] && !tmp[i])
		return (1);
	return (0);
}

int		is_env(char *str, int j)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_env_name_2check(str, ++j);
	if (is_path(tmp))
		return (2);
	while (global_env[i])
	{
		if (ft_envcmp(global_env[i], tmp))
			return (1);
		i++;
	}
	return (0);
}

void	dollar_deal(char *str, j)
{
	int ret;

	ret = is_env(lst->arg[i], j);
	if (ret == 1)
		r_dollar(lst->arg[i], j);
	if (ret == 2)
		r_path(lst->arg[i], j);
}

void	snr_dollar(t_list *lst)
{
	int	i;
	int j;

	i = 0;
	while (lst->arg[i])
	{
		j = 0;
		while (lst->arg[i][j])
		{
			if (lst->arg[i][j] == '$')
				dollar_deal(lst->arg[i], j);
			j++;
		}
		i++;
	}
}
