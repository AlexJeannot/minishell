/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:45:12 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 18:29:40 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_deleted(int *tab_index, int index)
{
    int count;

    count = 0;
    while (tab_index[count] != -1)
    {
        if (tab_index[count] == index)
            return (1);
        count++;
    }
    return (0);
}

char **cleared_env(char **from_array, char **output_array, int *tab_index)
{
    int count_tab;
    int count_add;

    count_tab = 0;
    count_add = 0;
    while (from_array[count_tab])
    {
        if (!(is_deleted(tab_index, count_tab)))
        {
            output_array[count_add] = from_array[count_tab];
            count_add++;
        }
        count_tab++;
    }
    output_array[count_add] = NULL;
    return (output_array);
}

void ft_unset(char *args)
{
    int count_tab;
    int count_add;
    int index;
    char **tab_args;
    char **new_env;
    int *tab_index;

    tab_args = ft_split(args, ' ');
    if (tab_args[0])
    {
        tab_index = malloc(sizeof(int) * array_length(tab_args));
        count_tab = 0;
        count_add = 0;
        while (tab_args[count_tab])
        {
            if ((index = search_in_array(global_env, tab_args[count_tab], '=')) >= 0)
            {
                tab_index[count_add] = index;
                count_add++;
            }
            count_tab++;
        }
        tab_index[count_add] = -1;
        new_env = malloc(sizeof(char *) * (array_length(global_env) - count_add + 1));
        new_env = cleared_env(global_env, new_env, tab_index);
        free_str_array(global_env);
        free(tab_index);
        free_str_array(tab_args);
        global_env = new_env;
    }
}
