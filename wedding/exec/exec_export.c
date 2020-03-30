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
    int count;
    char *output_str;

    count = 0;
    if (!(output_str = (char *)malloc(sizeof(char) * (ft_strlen(input_str) + 14))))
        display_error(NULL, NULL);
    while (input_str[count] != '=')
        count++;
    ft_strcpy(output_str, "declare -x ");
    ft_strncat(output_str, input_str, count + 1);
    ft_strcat(output_str, "\"");
    ft_strcat(output_str, &input_str[count + 1]);
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
    int count;
    char **output_array;

    count = 0;
    if (!(output_array = (char **)malloc(sizeof(char *) * (array_length(input_array) + 1))))
        display_error(NULL, NULL);
    while (input_array[count])
    {
        output_array[count] = transform_str(input_array[count]);
        count++;
    }
    output_array[count] = NULL;
    free_str_array(input_array);
    return (output_array);
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
    write(1, "Minishell: export: ", 19);
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

int export_without_args(char **input_array)
{
    if (!(input_array[0]) || input_array[0][0] == '$' || input_array[0][0] == '#')
        return (1);
    return (0);
}

void display_exported_env(void)
{
    char **displayable_env;

    displayable_env = duplicate_array(global_env, NULL, '\0');
    displayable_env = sort_array(displayable_env);
    displayable_env = transform_array(displayable_env);
    display_array(displayable_env);
    free_str_array(displayable_env);
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
    int equal_index;
    char **split_result;
    char **output_array;

    array_count = 0;
    add_count = 0;
    output_array = malloc(sizeof(char *) * (array_length(input_array) + 1));
    while (input_array[array_count])
    {
        split_result = ft_split(input_array[array_count], '=');
        if (is_valid_var(split_result[0]) == -1)
            display_invalid_export(split_result[0], 0);
        else if ((equal_index = find_car(input_array[array_count], '=')) != -1 && is_valid_value(&input_array[array_count][equal_index]) == -1)
            display_invalid_export(&input_array[array_count][equal_index], 1);
        else
            add_count = add_exported_var(input_array[array_count], output_array, add_count);
        array_count++;
    }
    output_array[add_count] = NULL;
    return (output_array);
}

void ft_export(char **args)
{
    char **add_array;

    add_array = NULL;
    if (export_without_args(args))
        display_exported_env();
    else
    {
        add_array = create_exported_var_array(args);
        global_env = extend_array(global_env, add_array, array_length(global_env), array_length(add_array));
    }
    free_str_array(args);
    free_str_array(add_array);
}
