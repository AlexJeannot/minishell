#include "minishell.h"

static t_value		new_cmd_value(int i)
{
	t_value	v;
	int		len;
	int		j;

	v.name = get_env_name_2check(lst->cmd, i);
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

static char*		get_cmd_env_value(int i)
{
	t_value v;

	v = new_cmd_value(i);
	v.y = 0;
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.j] = '\0';
	return (v.value);
}

static char	*get_cmd_startline(int i)
{
	char	*start;
	int		y;

	if (!(start = malloc(i)))
		ft_exit(1);
	y = 0;
	while (y < i)
	{
		start[y] = lst->cmd[y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

static char*	get_cmd_endline(int i)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	i++;
	while ((lst->cmd[i] >= '0' && lst->cmd[i] <= '9') || 
	(lst->cmd[i] >= 'a' && lst->cmd[i] <= 'z') ||
	(lst->cmd[i] >= 'A' && lst->cmd[i] <= 'Z'))
		i++;
	k = i;
	while (lst->cmd[i++])
		len++;
	if (!(end = malloc(len + 1)))
		ft_exit(1);
	len = 0;
	while (lst->cmd[k])
		end[len++] = lst->cmd[k++];
	end[len] = '\0';
	return (end);
}

static t_dolls		dolls_cmd_value(int i)
{
	t_dolls dls;

	dls.value = get_cmd_env_value(i);
	dls.startline = get_cmd_startline(i);
	dls.endline = get_cmd_endline(i);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}

static char*		r_cmd_dollar(int i)
{
	t_dolls dls;
	char	*res;
	int		j;

	dls = dolls_cmd_value(i);
	if (!(res = malloc(dls.len + 1)))
		ft_exit(1);
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

static int		quote_cmd_stop(int i)
{
	int	k;

	k = i;
	while (lst->cmd[i] != '\'' && lst->cmd[i])
		i--;
	while (lst->cmd[k] != '\'' && lst->cmd[k])
		k++;
	if (lst->cmd[k] == '\'' && lst->cmd[i] == '\'')
		return (1);
	return (0);
}

void	get_cmd_dollar(void)
{
	int	i;

	i = 0;
	while (lst->cmd[i])
	{
		if (lst->cmd[i] == '$' && !quote_cmd_stop(i) && !is_esc(lst->cmd, i))
		{
			if (is_env(lst->cmd, i))
				lst->cmd = r_cmd_dollar(i);
		}
		i++;
	}
}
