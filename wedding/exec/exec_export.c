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

#include "../includes/minishell.h"

char *transform_with_value(char *input_str)
{
    int str_count;
    char *output_str;

    str_count = 0;
    if (!(output_str = (char *)malloc(sizeof(char) * (ft_strlen(input_str) + 14))))
        display_error(NULL, NULL);
    while (input_str[str_count] != '=')
        str_count++;
    ft_strcpy(output_str, "declare -x ");
    ft_strncat(output_str, input_str, str_count + 1);
    ft_strcat(output_str, "\"");
    ft_strcat(output_str, &input_str[str_count + 1]);
    ft_strcat(output_str, "\"");
    return (output_str);
}

char *transform_without_value(char *input_str)
{
    char *output_str;

    if (!(output_str = (char *)malloc(sizeof(char) * (ft_strlen(input_str) + 12))))
        display_error(NULL, NULL);
    ft_strcpy(output_str, "declare -x ");
    ft_strcat(output_str, input_str);
    return (output_str);
}

char *transform_str(char *input_str)
{
    if (find_car(input_str, '=') != -1)
        return (transform_with_value(input_str));
    else
        return (transform_without_value(input_str));
}

char **transform_array(char **input_array)
{
    int tab_count;
    char **output_array;

    tab_count = 0;
    if (!(output_array = (char **)malloc(sizeof(char *) * (array_length(input_array) + 1))))
        display_error(NULL, NULL);
    while (input_array[tab_count])
    {
        output_array[tab_count] = transform_str(input_array[tab_count]);
        tab_count++;
    }
    output_array[tab_count] = NULL;
    free_str_array(input_array);
    return (output_array);
}

char **sort_env(void)
{
    char **new_env;

    new_env = duplicate_array(global_env, NULL, '\0');
    new_env = sort_array(new_env);
    new_env = transform_array(new_env);
    return (new_env);
}

int is_valid_var(char *str)
{
    int count;

    count = 1;
    if (str[0] < 'A'
    || (str[0] > 'Z' && str[0] < 'a')
    || str[0] > 'z')
        return (KO);
    while (str[count])
    {
        if (str[count] < '0'
        || (str[count] > '9' && str[count] < 'A')
        || (str[count] > 'Z' && str[count] < 'a' && str[count] != '_')
        || str[count] > 'z')
            return (KO);
        count++;
    }
    return (OK);
}

int is_valid_value(char *str)
{
    int count;

    count = 0;
    while (str[count] && str[count] != '=')
    {
        if (str[count] < '!' || str[count] == 127)
            return (KO);
        count++;
    }
    return (OK);
}

void display_invalid_export(char *str, int type)
{
    write(1, "Minishell: export: ", 11);
    write(1, "`", 1);
    if (!(type))
    {
        write(1, str, ft_strlen(str));
        write(1, "': not a valid identifier\n", 26);
    }
    if (type)
    {
        write(1, str, ft_strlen(str));
        write(1, "': not a valid value\n", 21);
    }
}

void ft_export(char **args)
{
    int array_count;
    int add_count;
    int equal_index;
    char *var;
    char **add_args;
    char **sorted_env;
    char **split_result;

    add_args = NULL;
    if (!(args[0]) || args[0][0] == '$' || args[0][0] == '#')
    {
        sorted_env = sort_env();
        display_array(sorted_env);
        free_str_array(sorted_env);
    }
    else
    {
        array_count = 0;
        add_count = 0;
        add_args = malloc(sizeof(char *) * (array_length(args) + 1));
        while (args[array_count])
        {
            split_result = ft_split(args[array_count], '=');
            if (is_valid_var(split_result[0]) == -1)
                display_invalid_export(split_result[0], 0);
            else if ((equal_index = find_car(args[array_count], '=')) != -1 && is_valid_value(&args[array_count][equal_index]) == -1)
                display_invalid_export(&args[array_count][equal_index], 1);
            else
            {
                var = ft_strdup(args[array_count]);
                add_args[add_count] = var;
                add_count++;
            }
            array_count++;
        }
        add_args[add_count] = NULL;
        global_env = extend_array(global_env, add_args, array_length(global_env), array_length(add_args));
    }
    free_str_array(args);
    if (add_args)
        free_str_array(add_args);
}
