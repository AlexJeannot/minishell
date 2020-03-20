#include "minishell.h"

static t_dolls		dolls_value(int i, int j, int ret)
{
	t_dolls dls;

	dls.value = get_env_value(i, j, ret);
	dls.startline = get_startline(i, j);
	dls.endline = get_endline(i, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}

//static void		r_dollar(int i, int j, int ret)
static char*		r_dollar(int i, int j, int ret)
{
	t_dolls dls;
	int		y;
	int		k;
	char	*res;

	dls = dolls_value(i, j, ret);
	if (!(res = malloc(dls.len + 1)))
		ft_exit(1);
	y = 0;
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
	return (res);
	//lst->arg[i] = res;
	//free(res);
}

static int		quote_stop(int i, int j)
{
	int	k;
	int ret;

	k = j;
	while (lst->arg[i][j] != '\'' && lst->arg[i][j])
		j--;
	while (lst->arg[i][k] != '\'' && lst->arg[i][k])
		k++;
	if (lst->arg[i][k] == '\'' && lst->arg[i][j] == '\'')
		ret = 1;
	else
		ret = 0;
	return (ret);
}

void	get_dollar(void)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (lst->arg[i])
	{
		j = 0;
		while (lst->arg[i][j])
		{
			if (lst->arg[i][j] == '$' && !quote_stop(i, j))
			{
				if ((ret = is_env(lst->arg[i], j)))
				{
					lst->arg[i] = r_dollar(i, j, ret);
					//r_dollar(i, j, ret);
				}
			}
			j++;
		}
		i++;
	}
}
