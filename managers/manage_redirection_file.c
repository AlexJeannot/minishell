/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:44:03 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/20 18:11:59 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	exec_file(int count)
{
	int	fd_file;

	if (lst->rdc_index[count][1] == 1)
	{
		if ((fd_file = open(lst->rdc_filetab[count],
		O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
			ft_error('\0', lst->rdc_filetab[count], NULL, 1);
	}
	if (lst->rdc_index[count][1] == 2)
	{
		if ((fd_file = open(lst->rdc_filetab[count],
		O_WRONLY | O_CREAT, 0644)) == -1)
			ft_error('\0', lst->rdc_filetab[count], NULL, 1);
	}
	close(fd_file);
}
