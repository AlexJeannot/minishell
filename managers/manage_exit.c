/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:41:10 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:41:41 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int		transform_status(char *input_str)
{
	int count;
	int final_status;
	unsigned long input_status;

	count = 0;
	input_status = 0;
	//printf("ENTREE transform_status\n");
	//printf("input_str = %s\n", input_str);
	if (input_str[count] == 43 || input_str[count == 45])
		count++;
	while (input_str[count])
	{
		if (input_str[count] < 48 || input_str[count] > 57)
			ft_error('\0', "exit", "numeric argument required");
		input_status = (input_status * 10) + (input_str[count] - 48);
		count++;
	}
	//printf("input_status = %lu\n", input_status);
	final_status = (int)(input_status % 256);
	//printf("final_status = %d\n", final_status);
	return (final_status);
}

void	ft_exit(int status)
{
	if (lst && lst->cmd && ft_strcmp(lst->cmd, "exit") == 0 && child_pid != 0)
	{
		//printf("ENTREE SI EXIT DANS FT_EXIT\n");
		//printf("--------- lst->arg ------------\n");
		//if (lst->arg)
		//	display_str_array(lst->arg);
		//printf("--------- lst->arg ------------\n");
		//if (str_array_length(lst->arg) > 1)
		//	write(1, "bash: exit: too many arguments", 30);
		//else if (str_array_length(lst->arg) == 1)
		//	status = transform_status(lst->arg[0]);
		//write(1, "exit\n", 5);
	}
	free_lst();
	free_str_array(filtered_env);
	free_str_array(global_env);
	exit(status);
}
