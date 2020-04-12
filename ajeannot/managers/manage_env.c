/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:46:22 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:49 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char *get_env_value(char *var)
{
    int count;

    count = 0;
    while (global_env[count])
    {
        if (strcmp(ft_split(global_env[count], '=')[0], var) == 0)
            return (ft_split(global_env[count], '=')[1]);
        count++;
    }
    return (NULL);
}
