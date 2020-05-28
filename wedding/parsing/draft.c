#include "../includes/parsing.h"

char	*get_startline(char *str, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		ft_error('\0', "Malloc", NULL);
	y = 0;
	while (y < j)
	{
		start[y] = str[y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char	*get_endline(char *str, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((str[j] >= '0' && str[j] <= '9') ||
			(str[j] >= 'a' && str[j] <= 'z') ||
			(str[j] >= 'A' && str[j] <= 'Z'))
		j++;
	k = j;
	while (str[j++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_error('\0', "Malloc", NULL);
	len = 0;
	while (str[k])
		end[len++] = str[k++];
	end[len] = '\0';
	return (end);
}

char	*get_env_name_2check(char *str, int j)
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

t_value	new_value(char *str, int j)
{
	t_value	v;
	int		len;
	int		i;

	v.name = get_env_name_2check(str, j);
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
	free_str(&v.name);
	return (v);
}

char	*get_env_value_2(char *str, int j)
{
	t_value v;

	v = new_value(str, j);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.y] = '\0';
	return (v.value);
}



t_dolls	dolls_value(char *str, int j)
{
	t_dolls dls;

	dls.value = get_env_value_2(str, j);
	dls.startline = get_startline(str, j);
	dls.endline = get_endline(str, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
		+ ft_strlen(dls.endline);
	return (dls);
}

char		*r_dollar(char *str, int j)
{
	t_dolls dls;
	char	*res;
	int		i;

	dls = dolls_value(str, j);
	if (!(res = malloc(dls.len + 1)))
		ft_error('\0', "Malloc", NULL);
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
	free_str(&str);
	free_str(&dls.value);
	free_str(&dls.startline);
	free_str(&dls.endline);
	return (res);
}

char	*get_dollar_str(char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && !quote_stop(str, j)
				&& !is_esc(str, j))
		{
			if (is_env(str, j))
				str = r_dollar(str, j);
		}
		j++;
	}
	return (str);
}

char	**get_dollar_tab(char **tab)
{
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '$' && !quote_stop(tab[i], j)
					&& !is_esc(tab[i], j))
			{
				if (is_env(tab[i], j))
					tab[i] = r_dollar(tab[i], j);
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	get_dollar(void)
{
	if (lst->cmd)
	{
		lst->cmd = get_dollar_str(lst->cmd);
		lst->arg = get_dollar_tab(lst->arg);
		lst->raw = get_dollar_tab(lst->raw);
	}
	if (lst->rdc_filetab)
		lst->rdc_filetab = get_dollar_tab(lst->rdc_filetab);
	if (lst->rdo_filetab)
		lst->rdo_filetab = get_dollar_tab(lst->rdo_filetab);
}
