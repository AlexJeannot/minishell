#include "minishell.h"

static int	is_pipe(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '|' && !is_esc(stock, i))
			return (1);
		i++;
	}
	return (0);
}

static t_cont get_content_lst(char *stock, int pipe)
{
	int		i;
	int		j;
	t_cont	cont;
	char	**content;

	cont = get_redir(stock);
	content = split_plus(stock, ' ');
	cont.cmd = content[0];
	i = 1;
	while (content[i])
		i++;
	if (!(cont.arg = malloc(sizeof(char*) * i + 1)))
		return (cont);
	i = 1;
	j = 0;
	while (content[i])
		cont.arg[j++] = content[i++];
	cont.arg[j] = NULL;
	cont.pipe = pipe; 
	return (cont);
}

static void	new_elem_lst(char *stock_elem, int pipe)
{
	t_list	*elem;
	t_list	*tmp;
	t_cont	cont;

	if (!(elem = malloc(sizeof(t_list))))
		ft_exit(1);
	cont = get_content_lst(stock_elem, pipe);
	elem->cmd = cont.cmd;
	elem->arg = cont.arg;
//	elem->rd_type = cont.rd_type;
//	elem->rd_filename = cont.rd_filename;
	elem->pipe = pipe;
	elem->next = NULL;
	if (is_empty_lst())
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
	pipe_sep = split_plus(stock_elem_piped, '|');
	while (pipe_sep[i] && is_valid(pipe_sep[i]))
	{
		new_elem_lst(pipe_sep[i], 1);
		i++;
	}
}

void	list_it(char **stock)
{
	int i;

	i = 0;
	while (stock[i] && is_valid(stock[i]))
	{
		if (!is_pipe(stock[i]))
			new_elem_lst(stock[i], 0);
		else
			list_pipe(stock[i]);
		i++;
	}
}
