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

char*		get_env_value(int i, int j, int ret)
{
	t_value v;

	v = new_value(i, j, ret);
	v.y = 0;
	//if (ret == 2)
	//	return (get_lil_path_value(v));
	while (global_env[v.i][v.j])
		v.value[v.y++] = global_env[v.i][v.j++];
	v.value[v.j] = '\0';
	return (v.value);
}

t_dolls		dolls_value(int i, int j, int ret)
{
	t_dolls dls;

	dls.value = get_env_value(i, j, ret);
	dls.startline = get_startline(i, j);
	dls.endline = " years old";//get_endline(i, j, dls);
	dls.len = ft_strlen(dls.value) + ft_strlen(dls.startline)
	+ ft_strlen(dls.endline);
	return (dls);
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
	lst->arg[i] = res;
	printf("res :%s\n", lst->arg[i]);
	free(res);
}

void	dollar_deal(int i, int j)
{
	int ret;

	if ((ret = is_env(lst->arg[i], j)))
		r_dollar(i, j, ret);
}

void	snr_dollar(void)
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

int main(int ac, char **av, char **env)
{
	t_list *elem;
	t_list *tmp;
	(void)ac;
	global_env = env;
	int a = 0;
	
	lst = NULL;
	while (a <= 5)
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
	while (lst)
	{
		snr_dollar();
		lst = lst->next;
	}
	return(0);
}
