/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:40:05 by cbouleng          #+#    #+#             */
/*   Updated: 2020/03/11 16:10:42 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing(char *line)
{
	char **stock;

	if (!(check_quote(line)))
		ft_exit(1);
	stock = split_plus(line, ';');
	stock = clean_esc_quote(stock); // free required ?
	list_it(stock);
	print_lst();
	return (1);
}

static void	init(char ac, char **av)
{
	if (ac != 1)
		ft_exit(1);
	(void)av;
	lst = new_lst();
}

int			main(int ac, char **av)
{
	char	*line;

	init(ac, av);
	prompt();
	while (1)
	{
		if (get_next_line(0, &line))
			prompt();
		parsing(line);
		//exec();
		clear_lst();
		free(line);
	}
	free(line);
	return (0);
}
