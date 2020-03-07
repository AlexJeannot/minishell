
#include "minishell.h"

static int	ft_exit(int status)
{
	exit(status);
}

static t_list	init(int ac, char **av, char **env)
{
	t_stt *vs;

	(void)av;
	if (ac != 1)
		return (ft_exit(1));
}

static int	is_pipe(char *stock)
{
	while (stock[i])
	{
		if (stock[i] == "|")
			return (1);
		i++;
	}
	return (0);
}

static void	prompt(t_stt *vs)
{
	if ()
		write(1, "$ ", 2);
}

static t_list	*new_trio(t_trio trio)
{
	t_list	*lst;

	if (!(lst = malloc(sizeof(t_list))))
		return (*lst);
	list->cmd = trio->cmd;
	list->arg = trio->arg;
	list->pipe = trio->pipe;
	list->next = NULL;
	return (lst);
}

static t_trio get_trio(char *stock, int pipe)
{
	int		i;
	int		j;
	char	**content;
	t_trio	trio;

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

static t_list	get_pipe_lst(char *stock, t_list *lst)
{
	int		i;
	char	**piped;
	t_list	elem;

	piped = ft_split_plus(stock, "|");
	while (piped[i])
	{
		elem = get_trio(piped[i], 1);
		if (!lst)
			lst = &elem;
		else
		{
			while (lst->next)
				lst = lst->next;
			lst->next = &elem;
		}
		i++;
		return (*lst);
}


static t_list	pre_list_it(t_stt vs)
{
	t_trio	content;
	t_list	*lst;

	if (!(lst = malloc(sizeof(t_list))) && lst = NULL)
		return (0);
	vs.i = 0;
	while (vs.stock[i])
	{
		if (!is_pipe(vs.stock[i]))
			elem = get_trio(vs.stock[i], 0)
		else
		{
			elem = get_pipe_lst(vs.stock[i]);
		}
	}
	return (elem);
}

static int	list_it(t_stt vs)
{
	t_lst *lst;	
	t_lst elem;	

	if (!(lst = malloc(sizeof(t_list))))
		return (0);
	lst = NULL;
	while (vs->stock[i])
	{
		elem = pre_list_it(vs);
		if (!lst)
			lst = &elem;
		else
		{
			while (lst->next)
				lst = lst->next;
			lst->next = &elem;
		}
		i++;
	}
	return (1);
}

static void	parsing(char *line, t_stt *vs)
{
	vs->stock = ft_split_plus(line, ";");		
	list_it(vs);
}

int		main(int ac, char **av, char **env)
{
	t_stt	vs;
	char 	*line;

	vs = init(ac, av, env);
	prompt(vs);
	while (!get_next_line(0, &line))
	{
		get_env(env, vs);
		parsing(line, vs);
		free(line);
		prompt(vs);
	}
	free(line);
	return (0);
}
