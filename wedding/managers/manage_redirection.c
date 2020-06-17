/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:51:39 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:54:10 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	check_rdo_exec(void)
{
	int count;
	int fd_file;

	count = 0;
	if (lst->rdo_type != 0)
	{
		while (lst->rdo_filetab[count])
		{
			if ((fd_file = open(lst->rdo_filetab[count], O_RDONLY)) == -1)
				return (count);
			close(fd_file);
			count++;
		}
	}
	return (-1);
}

void	manage_rdo_error(int ret_check)
{
	int count;
	int fd_file;

	count = 0;
	if (lst->rdc_filetab)
	{
		while (lst->rdc_filetab[count] && lst->rdc_index[count][0]
		< lst->rdo_index[ret_check][0])
		{
			if (lst->rdc_index[count][1] == 1)
			{
				if ((fd_file = open(lst->rdc_filetab[count],
				O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
					ft_error('\0', lst->rdc_filetab[count], NULL);
			}
			close(fd_file);
			count++;
		}
		ft_error('\0', lst->rdo_filetab[ret_check]
		, "No such file or directory");
	}
}

void	create_file(void)
{
	int count;
	int fd_file;

	count = 0;
	if (lst->rdc_filetab)
	{
		while (lst->rdc_filetab[count])
		{
			if ((fd_file = open(lst->rdc_filetab[count],
			O_CREAT, 0644)) == -1)
				ft_error('\0', lst->rdc_filetab[count], NULL);
			close(fd_file);
			count++;
		}
	}
}

void	red_stdout_in_file(void)
{
	int fd_file;

	if (lst->rdc_type == 1)
	{
		if ((fd_file = open(lst->rdc_filename, O_WRONLY | O_TRUNC)) == -1)
			ft_error('\0', lst->rdc_filename, NULL);
	}
	else
	{
		if ((fd_file = open(lst->rdc_filename, O_WRONLY | O_APPEND)) == -1)
			ft_error('\0', lst->rdc_filename, NULL);
	}
	dup2(fd_file, STDOUT_FILENO);
	close(fd_file);
}

void	manage_redirection(void)
{
	int ret_check;

	if ((ret_check = check_rdo_exec()) != -1)
		manage_rdo_error(ret_check);
	create_file();
	if (lst->rdc_type != 0)
		red_stdout_in_file();
}
