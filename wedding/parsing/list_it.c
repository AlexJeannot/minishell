#include "../includes/minishell.h"

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
	stock =	clear_stock_rd(stock);
	printf("[%s]\n", stock);
	content = split_plus(stock, ' ');
	cont.raw = content;
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
		ft_exit("malloc failed", 1);
	cont = get_content_lst(stock_elem, pipe);
	elem->cmd = cont.cmd;
	elem->arg = cont.arg;
	elem->raw = cont.raw;
	elem->rdc_type = cont.rdc_type;
	elem->rdo_type = cont.rdo_type;
	elem->rdc_filetab = cont.rdc_filetab;
	elem->rdo_filetab = cont.rdo_filetab;
	elem->rdc_filename = cont.rdc_filename;
	elem->rdo_filename = cont.rdo_filename;
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
