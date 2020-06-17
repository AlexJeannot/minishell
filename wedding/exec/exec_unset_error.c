/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:30:02 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:30:14 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	display_invalid_unset(char *str)
{
	write(2, "Minishell: unset: ", 18);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	verify_unset_var(char **input_array)
{
	int status;
	int array_count;

	status = 0;
	array_count = 0;
	while (input_array[array_count])
	{
		if (is_valid_var(input_array[array_count]) == -1)
			status = display_invalid_unset(input_array[array_count]);
		array_count++;
	}
	return (status);
}
