#include "minishell.h"

static t_dolls		dolls_value(int i, int j)
{
	t_dolls dls;

	dls.value = get_env_value(i, j);
	dls.startline = get_startline(i, j);
	dls.endline = get_endline(i, j);
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

static int		quote_stop(int i, int j)
{
	int	k;

	k = j;
	while (lst->arg[i][j] != '\'' && lst->arg[i][j])
		j--;
	while (lst->arg[i][k] != '\'' && lst->arg[i][k])
		k++;
	if (lst->arg[i][k] == '\'' && lst->arg[i][j] == '\'')
		return (1);
	return (0);
}

static int	export_case(int i, int j)
{
	if (!ft_strcmp(lst->cmd, "export") && is_env(lst->arg[i], j))
		return (1);
	return (0);
}

void	get_dollar(void)
{
	int	i;
	int	j;

	i = 0;
	get_cmd_dollar();
	while (lst->arg[i])
	{
		j = 0;
		while (lst->arg[i][j])
		{
			if (lst->arg[i][j] == '$' && !quote_stop(i, j) 
				&& !export_case(i, j) && !is_esc(lst->arg[i], j))
			{
				if (is_env(lst->arg[i], j))
					lst->arg[i] = r_dollar(i, j);
			}
			j++;
		}
		i++;
	}
}
