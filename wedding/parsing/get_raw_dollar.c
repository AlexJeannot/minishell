#include "../includes/parsing.h"

char	*raw_get_startline(int i, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		ft_exit("malloc failed", 1);
	y = 0;
	while (y < j)
	{
		start[y] = lst->raw[i][y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char*	raw_get_endline(int i, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((lst->raw[i][j] >= '0' && lst->raw[i][j] <= '9') ||
	(lst->raw[i][j] >= 'a' && lst->raw[i][j] <= 'z') ||
	(lst->raw[i][j] >= 'A' && lst->raw[i][j] <= 'Z'))
		j++;
	k = j;
	while (lst->raw[i][j++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_exit("malloc failed", 1);
	len = 0;
	while (lst->raw[i][k])
		end[len++] = lst->raw[i][k++];
	end[len] = '\0';
	return (end);
}


static t_value		raw_new_value(int i, int j)
{
	t_value	v;
	int		len;

	v.name = get_env_name_2check(lst->raw[i], j);
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
		ft_exit("malloc failed", 1);
	return (v);
}

char*		get_env_value_3(int i, int j)
{
	t_value v;

	v = raw_new_value(i, j);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.j] = '\0';
	return (v.value);
}

static t_dolls		dolls_value(int i, int j)
{
	t_dolls dls;

	dls.value = get_env_value_3(i, j);
	dls.startline = raw_get_startline(i, j);
	dls.endline = raw_get_endline(i, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}

static char*		r_dollar(int i, int j)
{
	t_dolls dls;
	char	*res;

	dls = dolls_value(i, j);
	if (!(res = malloc(dls.len + 1)))
		ft_exit("malloc failed", 1);
	i = 0;
	while (dls.startline[i])
	{
		res[i] = dls.startline[i];
		i++;
	}
	j = 0;
	while (dls.value[j])
		res[i++] = dls.value[j++];
	j = 0;
	while (dls.endline[j])
		res[i++] = dls.endline[j++];
	res[i] = '\0';
	return (res);
}

static int	quote_stop(int i, int j)
{
	int	k;

	k = j;
	while (lst->raw[i][j] != '\'' && lst->raw[i][j])
		j--;
	while (lst->raw[i][k] != '\'' && lst->raw[i][k])
		k++;
	if (lst->raw[i][k] == '\'' && lst->raw[i][j] == '\'')
		return (1);
	return (0);
}

void	get_raw_dollar(void)
{
	int	i;
	int	j;

	i = 0;
	while (lst->raw[i])
	{
		j = 0;
		while (lst->raw[i][j])
		{
			if (lst->raw[i][j] == '$' && !quote_stop(i, j)
				&& !is_esc(lst->raw[i], j))
			{
				if (is_env(lst->raw[i], j))
					lst->raw[i] = r_dollar(i, j);
			}
			j++;
		}
		i++;
	}
}
