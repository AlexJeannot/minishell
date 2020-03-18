#include "minishell.h"

void
	quote_env()
{
	if (str[j - 1] == ''')
	{
		j++;
		while (str[j] && str[j] != ' ')
			j++;
	}
}

void
	double_quote_env()
{

}

char
	*get_env_name_2check(char *str, int j)
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

int
	ft_envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && !s2[i])
		return (1);
	return (0);
}

int
	is_path(char *str)
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

int
	is_env(char *str, int j)
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
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

t_value
	new_value(int i, int j, int ret)
{
	t_value v;

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
	while (global_env[i][++j])
		len++;
	if (!(value = malloc(len + 1)))
		ft_exit(1);
	v.i = i;
	v.j = j + 1;
	return (v);
}

char*
	get_lil_path_value(t_value v)
{
	int	y;

	y = 0;
	while (global_env[v.i][v.j])
	{
		if (global_env[v.i][v.j] == ':')
			value[y] = ' ';
		else
			value[y] = global_env[v.i][v.j];
		y++;
		v.j++;
	}
	value[y] = '\0';
	return (value);
}

char*
	get_env_value(int i, int j, int ret)
{
	t_value v;

	v = new_value(i, j, ret);
	if (ret == 2)
		return (get_lil_path_value(v));
	while (global_env[v.i][v.j]
		value[y++] = global_env[v.i][v.j++];
	value[v.j] = '\0';
	return (value);
}

char *
	get_startline(int i, int j)
{
	char *start;

	if (!(start = malloc(j)))
		ft_exit(1);
	while (y < j)
	{
		start[y] = lst->arg[i][y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char *
	get_endline(int i, int j, t_dolls dls)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	k = j + 1;
	value_len = ft_strlen(dls.value);
	while (value_len)
	{
		j++;
		value_len--;
	}
	while (lst->arg[i][j])
	{
		j++;
		len++;
	}
	if (!(end = malloc(len + 1)))
		ft_exit(1);
	len = 0;
	while (k < j)
		end[len++] = lst->arg[i][k++];
	end[len] = '\0';
	return (end);
}

t_dolls
	dolls_value(int i, int j, int ret)
{
	t_dolls dls;

	dls.value = get_env_value(i, j, ret);
	dls.startline = get_startline(i, j);
	dls.endline = get_endline(i, j, dls);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}

void
	r_dollar(int i, int j, int ret)
{
	t_dolls dls;
	int		k;

	dls = dolls_value(i, j, ret);
	if (!(res = malloc(dls.len + 1)))
		ft_exit(1);
	while (dls.startline[y])
	{
		res[y] = dls.startline[y];
		y++;
	}
	k = 0;
	while (dls.value[k])
		res[y++] = dls.value[k++];
	k = 0;
	while (dls.endline[k])
		res[y++] = dls.endline[k++];
	res[y] = '\0';
	lst->arg[i] = res;
	free(res);
}

void
	dollar_deal(int i, int j)
{
	int ret;

	if (ret = is_env(lst->arg[i], j))
		r_dollar(lst->arg[i], j, ret);
}

void
	snr_dollar(t_list *lst)
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
				dollar_deal(i, j);
			j++;
		}
		i++;
	}
}
