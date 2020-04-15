/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:08:28 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:45:17 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int export_without_args(char **input_array)
{
    printf("input_array[0] = %s\n", input_array[0]);
    if (!(input_array[0]) || input_array[0][0] == '#')
        return (1);
    if (input_array[0][0] == '$' && input_array[0][1] == '@')
        return (1);
    if (input_array[0][0] == '$' && is_valid_var(&input_array[0][1]) == 1)
        return (1);
    return (0);
}

int add_exported_var(char *input_str, char **output_array, int add_count)
{
    char *add_var;

    add_var = ft_strdup(input_str);
    output_array[add_count] = add_var;
    add_count++;
    return (add_count);
}

char **create_exported_var_array(char **input_array)
{
    int array_count;
    int add_count;
    char **split_result;
    char **output_array;

    array_count = 0;
    add_count = 0;
    output_array = malloc(sizeof(char *) * (str_array_length(input_array) + 1));
    while (input_array[array_count])
    {
        split_result = ft_split(input_array[array_count], '=');
        add_count = add_exported_var(input_array[array_count], output_array, add_count);
        array_count++;
    }
    output_array[add_count] = NULL;
    free_str_array(split_result);
    return (output_array);
}

int ft_export(char **args)
{
    int     status;
    char **add_array;

    status = 0;
    add_array = NULL;
    if (export_without_args(args))
        display_exported_env();
    else
    {
        status = verify_exported_var(args);
        add_array = create_exported_var_array(args);
        global_env = extend_array(global_env, add_array, str_array_length(global_env), str_array_length(add_array));
    }
    free_str_array(args);
    free_str_array(add_array);
    return (status);
}
