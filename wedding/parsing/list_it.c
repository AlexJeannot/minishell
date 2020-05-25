/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:04:17 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 17:17:41 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static t_cont	get_content_lst(char *stock, int pipe)
{
	int		i;
	int		j;
	t_cont	cont;
	char	**content;

	cont = get_redir(stock);
	stock = clear_stock_rd(stock);
	content = split_plus(stock, ' ');
	cont.raw = duplicate_array(content, NULL, '\0');
	cont.cmd = ft_strdup(content[0]);
	i = 0;
	while (content[i])
		i++;
	if (!(cont.arg = malloc(sizeof(char*) * i)))
		ft_error('\0', "Malloc", NULL);
	i = 1;
	j = 0;
	while (content[i])
		cont.arg[j++] = ft_strdup(content[i++]);
	cont.arg[j] = NULL;
	cont.pipe = pipe;
	free_str_array(content);
	return (cont);
}

static void		new_elem_lst(t_list *elem)
{
	t_list	*tmp;

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

static void		new_elem_lst(char *stock_elem, int pipe)
{
	t_list	*elem;
	t_cont	cont;

	if (!(elem = malloc(sizeof(t_list))))
		ft_error('\0', "Malloc", NULL);
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
	elem->rdc_index = cont.rdc_index;
	elem->rdo_index = cont.rdo_index;
	elem->pipe = pipe;
	elem->next = NULL;
	new_elem_lst_2(elem);
}

static void		list_pipe(char *stock_elem_piped)
{
	int		i;
	char	**pipe_sep;

	i = 0;
	pipe_sep = split_plus(stock_elem_piped, '|');
	free_str(&stock_elem_piped);
	while (pipe_sep[i] && is_valid(pipe_sep[i]))
	{
		if (pipe_sep[i + 1] != NULL)
			new_elem_lst(pipe_sep[i], 1);
		else
			new_elem_lst(pipe_sep[i], 0);
		i++;
	}
	free_str_array(pipe_sep);
}

void			list_it(char **stock)
{
	int i;

	i = 0;
	while (stock[i] && is_valid(stock[i]))
	{
		if (!is_pipe(stock[i]))
		{
			new_elem_lst(stock[i], 0);
			free_str(&stock[i]);
		}
		else
			list_pipe(stock[i]);
		i++;
	}
}
