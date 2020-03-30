#include "minishell.h"

static int	parsing(char *line)
{
	char **stock;
	
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
			clear_backslash();
		//	clean_before_print();
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
