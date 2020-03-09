
#include "minishell.h"

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

static void		print_lst(t_stt *vs)
{
	t_list *tmp;
	int 	i;
	int		j;

	tmp = vs->lst;
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
	t_uti	u;
	t_trio	trio;
	char	**content;

	content = ft_split_plus(stock, " ");
	trio.cmd = content[0];
	u.i = 1;
	while (content[u.i])
		u.i++;
	if (!(trio.arg = malloc(sizeof(char*) * u.i + 1)))
		return (trio);
	u.i = 1;
	u.j = 0;
	while (content[u.i])
		trio.arg[u.j++] = content[u.i++];
	trio.arg[u.j] = NULL;
	trio.pipe = pipe; 
	return (trio);
}

static void	new_elem_lst(t_stt *vs, char *stock_elem, int pipe)
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
	if (is_empty_lst(vs->lst))
		vs->lst = elem;
	else
	{
		tmp = vs->lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}

static void list_pipe(char *stock_elem_piped, t_stt *vs)
{
	int		i;
	char	**pipe_sep;

	i = 0;
	pipe_sep = ft_split_plus(stock_elem_piped, "|");
	while (pipe_sep[i])
	{
		new_elem_lst(vs, pipe_sep[i], 1);
		i++;
	}
}

static void	list_it(char **stock, t_stt *vs)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (!is_pipe(stock[i]))
			new_elem_lst(vs, stock[i], 0);
		else
			list_pipe(stock[i], vs);
		i++;
	}
}

static int	parsing(char *line, t_stt *vs)
{
	char **stock;

	stock = ft_split_plus(line, ";");		
	list_it(stock, vs);
	print_lst(vs);
	return (1);
}

static t_stt	*init(char ac, char **av)
{
	t_stt *vs;

	if (ac != 1)
		return (0);
	(void)av;
	if (!(vs = malloc(sizeof(t_stt))))
		return (0);
	vs->lst = new_list();
	return (vs);
}

int		main(int ac, char **av)
{
	t_stt	*vs;
	char	*line;

	vs = init(ac, av);
	prompt();
	while (1)
	{
		if (get_next_line(0, &line))
			prompt();
		parsing(line, vs);
		free(line);
	}
	free(line);
	return (0);
}
