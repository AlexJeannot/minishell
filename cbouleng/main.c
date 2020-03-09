
#include "minishell.h"

t_list *lst;

static int	ft_exit(int status)
{
	exit(status);
}

static int	is_pipe(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

static void	prompt()
{
	write(1, "$ ", 2);
}

static t_list	*new_list(void)
{
	return (NULL);
}

static bool		is_empty_lst(t_list *lst)
{
	if (!lst)
		return (true);
	return (false);
}

static void		print_lst(void)
{
	t_list *tmp;
	int 	i;
	int		j;

	tmp = lst;
	j = 0;
	while (tmp)
	{
		printf("[%d]", j++);
		printf("cmd: %s }", tmp->cmd);
		i = 0;
		while (tmp->arg[i])
		{
			printf(".%s", tmp->arg[i]);
			i++;
		}
		printf("(%d)\n", tmp->pipe);
		tmp = tmp->next;
	}
}

static t_trio get_content_lst(char *stock, int pipe)
{
	int		i;
	int		j;
	t_trio	trio;
	char	**content;

	content = ft_split_plus(stock, " ");
	trio.cmd = content[0];
	i = 1;
	while (content[i])
		i++;
	if (!(trio.arg = malloc(sizeof(char*) * i + 1)))
		return (trio);
	i = 1;
	j = 0;
	while (content[i])
		trio.arg[j++] = content[i++];
	trio.arg[j] = NULL;
	trio.pipe = pipe; 
	return (trio);
}

static void	new_elem_lst(char *stock_elem, int pipe)
{
	t_list	*elem;
	t_list	*tmp;
	t_trio	trio;

	if (!(elem = malloc(sizeof(t_list))))
		ft_exit(1);
	trio = get_content_lst(stock_elem, pipe);
	elem->cmd = trio.cmd;
	elem->arg = trio.arg;
	elem->pipe = pipe;
	elem->next = NULL;
	if (is_empty_lst(lst))
		lst = elem;
	else
	{
		tmp = lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}

static void list_pipe(char *stock_elem_piped)
{
	int		i;
	char	**pipe_sep;

	i = 0;
	pipe_sep = ft_split_plus(stock_elem_piped, "|");
	while (pipe_sep[i])
	{
		new_elem_lst(pipe_sep[i], 1);
		i++;
	}
}

static void	list_it(char **stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (!is_pipe(stock[i]))
			new_elem_lst(stock[i], 0);
		else
			list_pipe(stock[i]);
		i++;
	}
}

static int	parsing(char *line)
{
	char **stock;

	stock = ft_split_plus(line, ";");		
	list_it(stock);
	print_lst();
	return (1);
}

static int	init(char ac, char **av)
{
	if (ac != 1)
		return (0);
	(void)av;
	lst = new_list();
	return (1);
}

int		main(int ac, char **av)
{
	char	*line;

	if (init(ac, av))
	{
		prompt();
		while (1)
		{
			if (get_next_line(0, &line))
				prompt();
			parsing(line);
			free(line);
		}
		free(line);
	}
	return (0);
}
