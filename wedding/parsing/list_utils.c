/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:18:22 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/25 17:20:02 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

t_list		*new_lst(void)
{
	return (NULL);
}

bool		is_empty_lst(void)
{
	if (!lst)
		return (true);
	return (false);
}

void		clear_lst_content(void)
{
	t_list *tmp;

	tmp = lst_free;
	while (lst_free)
	{
		free_str(&lst_free->cmd);
		free_str_array(lst_free->raw);
		free_str_array(lst_free->arg);
		free_str_array(lst_free->rdc_filetab);
		free_str_array(lst_free->rdo_filetab);
		free_int_array(lst_free->rdc_index);
		free_int_array(lst_free->rdo_index);
		lst_free = lst_free->next;
	}
	lst_free = tmp;
}

void		clear_lst(void)
{
	t_list *tmp;

	while (lst_free)
	{
		tmp = lst_free;
		lst_free = lst_free->next;
		free(tmp);
		tmp = NULL;
	}
}

void		free_lst(void)
{
	clear_lst_content();
	clear_lst();
}
