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

int is_unset(int *index_array, int index)
{
    int count;

    count = 0;
    while (index_array[count] != -1)
    {
        if (index_array[count] == index)
            return (1);
        count++;
    }
    return (0);
}

char **clear_env(char **input_array, int *index_array)
{
    int add_count;
    int array_count;
    char **output_array;

    add_count = 0;
    array_count = 0;
    if (!(output_array = (char **)malloc(sizeof(char *) * (array_length(input_array) - int_array_length(index_array) + 1))))
        display_error(NULL, NULL);
    while (input_array[array_count])
    {
        if (!(is_unset(index_array, array_count)))
        {
            output_array[add_count] = ft_strdup(input_array[array_count]);
            add_count++;
        }
        array_count++;
    }
    output_array[add_count] = NULL;
    free_str_array(input_array);
    return (output_array);
}

void display_invalid_unset(char *str)
{
    write(1, "Minishell: unset: ", 18);
    write(1, "`", 1);
    write(1, str, ft_strlen(str));
    write(1, "': not a valid identifier\n", 26);
}

int *create_unset_index_array(char **input_array)
{
    int index;
    int add_count;
    int array_count;
    int *index_array;

    if (!(index_array = (int *)malloc(sizeof(int) * (array_length(input_array) + 1))))
        display_error(NULL, NULL);
    add_count = 0;
    array_count = 0;
    while (input_array[array_count])
    {
        if (is_valid_var(input_array[array_count]) == -1)
            display_invalid_unset(input_array[array_count]);
        else if ((index = search_in_array(global_env, input_array[array_count], '=')) >= 0)
        {
            index_array[add_count] = index;
            add_count++;
        }
        array_count++;
    }
    index_array[add_count] = -1;
    return (index_array);
}

void ft_unset(char **args)
{
    int *index_array;

    if (args[0])
    {
        index_array = create_unset_index_array(args);
        global_env = clear_env(global_env, index_array);
        free(index_array);
    }
}
