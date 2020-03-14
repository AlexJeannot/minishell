#include "../includes/minishell.h"

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

static t_quatro get_content_lst(char *stock, int pipe)
{
	int		i;
	int		j;
	t_quatro	quatro;
	char	**content;

	content = split_plus(stock, ' ');
	quatro.cmd = content[0];
	i = 1;
	while (content[i])
		i++;
	if (!(quatro.raw = malloc(sizeof(char *) * (array_length(content) + 1))))
		return (quatro);
	quatro.raw = content;
	if (!(quatro.arg = malloc(sizeof(char*) * i + 1)))
		return (quatro);
	i = 1;
	j = 0;
	while (content[i])
		quatro.arg[j++] = content[i++];
	quatro.arg[j] = NULL;
	quatro.pipe = pipe;
	return (quatro);
}

static void	new_elem_lst(char *stock_elem, int pipe)
{
	t_list	*elem;
	t_list	*tmp;
	t_quatro	quatro;

	if (!(elem = malloc(sizeof(t_list))))
		ft_exit(NULL, 1);
	quatro = get_content_lst(stock_elem, pipe);
	elem->raw = quatro.raw;
	elem->cmd = quatro.cmd;
	elem->arg = quatro.arg;
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
	while (pipe_sep[i + 1] && is_valid(pipe_sep[i]))
	{
		new_elem_lst(pipe_sep[i], 1);
		i++;
	}
	new_elem_lst(pipe_sep[i], 0);
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

void		print_lst(void)
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

t_list	*new_lst(void)
{
	return (NULL);
}

bool		is_empty_lst()
{
	if (!lst)
		return (true);
	return (false);
}

int	is_valid(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	del_first(void)
{
	t_list *elem;

	if (is_empty_lst())
		lst = new_lst();
	if (!(elem = malloc(sizeof(t_list))))
		ft_exit(NULL, 1);
	elem = lst->next;
	free(lst);
	lst = elem;
}

void	clear_lst()
{
	if (is_empty_lst())
		new_lst();
	else
		while (lst)
			del_first();
}
