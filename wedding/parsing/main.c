/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:20:32 by cbouleng          #+#    #+#             */
/*   Updated: 2020/06/10 12:17:25 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	parsing(char *line)
{
	char **stock;

	printf("[%s]\n", line);
	check(line);
	stock = split_plus(line, ';');
	list_it(stock);
	if (stock)
	{
		free(stock);
		stock = NULL;
	}
}
