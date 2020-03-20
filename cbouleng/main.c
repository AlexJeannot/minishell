/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:40:05 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/12 09:19:56 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing(char *line)
{
	char **stock;

	stock = split_plus(line, ';');
	stock = clean_esc_quote(stock);
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
