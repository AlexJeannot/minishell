#include "minishell.h"

char* map;

static void	check_simple_quote(char* str)
{
	int i;
	
	i = 0;
	while (map[i])
	{
		if (map[i] == '3')
		{
			i++;
			while (map[i] == '1')
				i++;
			if (map[i] != '3' || str[i] != '\'')
				ft_exit(1);
		}
		i++;
	}
}

static void	check_double_quote(char* str)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '4')
		{
			i++;
			while (map[i] == '2')
				i++;
			if (map[i] != '4' || str[i] != '"')
				ft_exit(1);
		}
		i++;
	}
}

void		check_bs(char* str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i > 0)
	{
		if (str[i] == '\\' && (!str[i + 1] || str[i + 1] == ' ') &&  map[i] == '0')
		{
			if (!is_esc(str, i))
				ft_exit(1);
			else
				return ;
		}
		i--;
	}
}

static int	parsing(char *line)
{
	char **stock;

	map = map_quote(line, 0);
	check_simple_quote(line);
	check_double_quote(line);
	check_bs(line);
	stock = split_plus(line, ';');
	list_it(stock);
	return (1);
}

static void	init(char ac, char **av, char **env)
{
	if (ac != 1)
		ft_exit(1);
	(void)av;
	lst = new_lst();
	global_env = env;
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	t_list	*tmp;

	init(ac, av, env);
	prompt();
	while (1)
	{
		if (get_next_line(0, &line))
			prompt();
		parsing(line);
		tmp = lst;
		while (lst)
		{
			get_dollar();
			clear_before_print();
			lst = lst->next;
		}
		lst = tmp;
		print_lst();
		clear_lst();
		free(line);
	}
	free(line);
	return (0);
}
