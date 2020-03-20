#include "minishell.h"

char **global_env;

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
		exit(1);
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
		exit(1);
	return (v);
}

char*		get_lil_path_value(t_value v)
{
	int	y;

	y = 0;
	while (global_env[v.i][v.j])
	{
		if (global_env[v.i][v.j] == ':')
			v.value[y] = ' ';
		else
			v.value[y] = global_env[v.i][v.j];
		y++;
		v.j++;
	}
	v.value[y] = '\0';
	return (v.value);
}

char*		get_env_value(int i, int j, int ret)
{
	t_value v;

	v = new_value(i, j, ret);
	v.y = 0;
	if (ret == 2)
		return (get_lil_path_value(v));
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.j] = '\0';
	return (v.value);
}

char	*get_startline(int i, int j)
{
	char	*start;
	int		y;

	if (!(start = malloc(j)))
		exit(1);
	y = 0;
	while (y < j)
	{
		start[y] = lst->arg[i][y];
		y++;
	}
	start[y] = '\0';
	return (start);
}

char*	get_endline(int i, int j)
{
	char	*end;
	int		len;
	int		k;

	len = 0;
	j++;
	while ((lst->arg[i][j] >= '0' && lst->arg[i][j] <= '9') || 
	(lst->arg[i][j] >= 'a' && lst->arg[i][j] <= 'z') ||
	(lst->arg[i][j] >= 'A' && lst->arg[i][j] <= 'Z'))
		j++;
	k = j;
	while (lst->arg[i][j++])
		len++;
	if (!(end = malloc(len + 1)))
		exit(1);
	len = 0;
	while (lst->arg[i][k])
		end[len++] = lst->arg[i][k++];
	end[len] = '\0';
	return (end);
}

t_dolls		dolls_value(int i, int j, int ret)
{
	t_dolls dls;

	dls.value = get_env_value(i, j, ret);
	dls.startline = get_startline(i, j);
	dls.endline = get_endline(i, j);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
}

void	print_lst(void)
{
	t_list *tmp;
	int		i;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (tmp->arg[i])
			printf("[%s]", tmp->arg[i++]);
		printf("\n");
		tmp = tmp->next;
	}
}

void	copy_res(int i, char *res)
{
	int y;
	char **tmp;

	y = 0;
	while (lst->arg[y])
		y++;
	if (!(tmp = malloc(sizeof(char*) * y + 1)))
		exit(1);
	y = 0;
	while (lst->arg[y])
	{
		if (y != i)
			tmp[y] = lst->arg[y];
		y++;
	}
	tmp[i] = res;
	tmp[y] = NULL;
	lst->arg = tmp;
}

void	r_dollar(int i, int j, int ret)
{
	t_dolls dls;
	int		y;
	int		k;
	char	*res;

	dls = dolls_value(i, j, ret);
	if (!(res = malloc(dls.len + 1)))
		exit(1);
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
	copy_res(i, res);
	free(res);
}

void	dollar_deal(int i, int j)
{
	int ret;

	if ((ret = is_env(lst->arg[i], j)))
		r_dollar(i, j, ret);
}

int		quote_stop(int i, int j)
{
	int	k;

	k = j;
	while (lst->arg[i][j] != '\'' && lst->arg[i][j])
		j--;
	while (lst->arg[i][k] != '\'' && lst->arg[i][k])
		k++;
	if (k == '\'' && j == '\'')
		return (1);
	return (0);
}

void	get_dollar(void)
{
	int	i;
	int j;

	i = 0;
	while (lst->arg[i])
	{
		j = 0;
		while (lst->arg[i][j])
		{
			printf("%c", lst->arg[i][j]);
			if (lst->arg[i][j] == '$' && !quote_stop(i, j))
			{
				dollar_deal(i, j);
			}
			j++;
		}
				printf("@\n");
		printf("\n");
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_list *elem;
	t_list *tmp;
	(void)ac;
	global_env = env;
	int a = 0;
	
	lst = NULL;
	while (a < 5)
	{
		elem = malloc(sizeof(t_list));
		elem->arg = av;
		elem->next = NULL;
		if (a == 0)
			lst = elem;
		else
		{
			tmp = lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = elem;
		}
		a++;
	}
	tmp = lst;
	while (tmp)
	{
		get_dollar();
		tmp = tmp->next;
	}
	return(0);
}
