#include "../includes/minishell.h"

char* map;


int	parsing(char *line)
{
	char **stock;

	map = map_quote(line, 0);
	check(line);
	stock = split_plus(line, ';');
	list_it(stock);
	return (1);
}
/*
static void	init(char ac, char **av, char **env)
{
	if (ac != 1)
		ft_exit("one parameter required", 1);
	(void)av;
	lst = new_lst();
	global_env = env;
}
*/

//int			main(int ac, char **av, char **env)
//{
//	char	*line;
//	t_list	*tmp;
//	int		fd;
//	int	ret;
//
//	if (!(fd = open("tests.txt", O_RDONLY)))
//		ft_exit("open failed", 1);
//	init(ac, av, env);
////	prompt();
//	while (1)
//	{
//		ret = get_next_line(fd, &line);
//		parsing(line);
//		tmp = lst;
//		while (lst)
//		{
//			get_dollar();
//			clear_before_print();
//			lst = lst->next;
////		test_elem()
//		}
//		lst = tmp;
//		print_lst();
//		clear_lst();
//		free(line);
//		if (!ret)
//			break ;
//	}
//	free(line);
//	return (0);
//}
/*
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
*/
