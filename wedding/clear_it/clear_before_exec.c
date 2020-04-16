#include "../includes/parsing.h"

char*	map;

static int	nb_del_quote(char* str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0 && map[i] == '4')
			nb++;
		else if (map[i] == '3' || map[i] == '4')
			nb++;
		else if (map[i] == '4' && !map[i + 1])
			nb++;
		else if (str[i] == '\\' && str[i + 1] == '"' && map[i] != '1')
			nb++;
		i++;
	}
	return (nb);
}

static int	to_print(char* str, int i)
{
	if (map[i] == '1')
		return (1);
	if (str[i] == '"' && !str[i + 1] && map[i] == '2')
		return (0);
	if (str[i] == '\\' && !is_esc(str, i) && (str[i + 1] == '"'
		|| str[i + 1] == '\'') && map[i] == '0')
		return (0);
	if (str[i] == '\\' && str[i + 1] == '"' && str[i + 2])
		return (0);
	if (map[i] == '3' || map[i] == '4')
		return (0);
	return (1);
}

static char*	clear_quote(char* str)
{
	char*	res;
	int		nb;
	int		j;
	int		k;

	map = map_quote(str, 1);
	nb = nb_del_quote(str);
//	printf("quote[%d][%s]\n", nb, str);
	if (!(res = malloc(ft_strlen(str) - nb + 1)))
		ft_error('\0', "Malloc", NULL);
	j = 0;
	k = 0;
	while (str[j])
	{
		if (to_print(str, j))
			res[k++] = str[j];
		j++;
	}
	res[k] = '\0';
	//printf("cl_k[%d]\n", k);
	free_str(&map);
	free_str(&str);
	return (res);
}

int count_valid_str(char **input_array)
{
	int size;
	int array_count;

	array_count = 0;
	size = 0;
	while (input_array[array_count])
	{
		if ((input_array[array_count][0]))
			size++;
		array_count ++;
	}
	return (size);
}

char **clean_array(char **input_array)
{
	int size;
	int add_count;
	int array_count;
	char **output_array;

	array_count = 0;
	size = count_valid_str(input_array);
	if (!(output_array = (char **)malloc(sizeof(char*) * (size + 1))))
		ft_error('\0', "Malloc", NULL);
	array_count = 0;
	add_count = 0;
	while (input_array[array_count])
	{
		if ((input_array[array_count][0]))
		{
			output_array[add_count] = ft_strdup(input_array[array_count]);
			add_count++;
		}
		array_count ++;
	}
	output_array[add_count] = NULL;
	free_str_array(input_array);
	return (output_array);
}

char *clean_cmd(char *input_str)
{
	if (!(input_str[0]))
	{
		free_str(&input_str);
		if (lst->raw[0])
			input_str = ft_strdup(lst->raw[0]);
	}
	return (input_str);

}

void	clear_before_exec(void)
{
	int	i;

	i = 0;
	clear_backslash();
	lst->cmd = clear_echo_bad_env(lst->cmd);
	lst->cmd = clear_quote(lst->cmd);
	while (lst->arg[i])
	{
		lst->arg[i] = clear_echo_bad_env(lst->arg[i]);
		lst->arg[i] = clear_quote(lst->arg[i]);
		i++;
	}
	i = 0;
	while (lst->raw[i])
	{
		lst->raw[i] = clear_echo_bad_env(lst->raw[i]);
		lst->raw[i] = clear_quote(lst->raw[i]);
		i++;
	}
	lst->raw = clean_array(lst->raw);
	lst->arg = clean_array(lst->arg);
	lst->cmd = clean_cmd(lst->cmd);
}
