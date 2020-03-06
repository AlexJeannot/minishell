/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:26:14 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:47 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int array_length(char **input_array)
{
    int count;

    count = 0;
    if (input_array)
        while (input_array[count])
            count++;
    else
        return (KO);
    return (count);
}

char **duplicate_array(char **input_array, char sep)
{
    int count;
    int array_len;
    char **output_array;

    count = 0;
    array_len = array_length(input_array);
    output_array = (char **)malloc(sizeof(char *) * (array_len + 1));
    while (input_array[count])
    {
        if (sep)
            output_array[count] = ft_strdup(ft_split(input_array[count], sep)[0]);
        else
            output_array[count] = ft_strdup(input_array[count]);
        count++;
    }
    output_array[count] = NULL;
    return (output_array);
}

char **sort_array(char **input_array)
{
    int tab_count;
    int sort_count;
    char *str_tmp;

    tab_count = 0;
    while (input_array[tab_count])
    {
        sort_count = tab_count;
        while (input_array[sort_count + 1])
        {
            if ((strcmp(input_array[sort_count], input_array[sort_count + 1])) > 0)
            {
                str_tmp = input_array[sort_count];
                input_array[sort_count] = input_array[sort_count + 1];
                input_array[sort_count + 1] = str_tmp;
                sort_count = tab_count;
            }
            else
                sort_count++;
        }
        tab_count++;
    }
    return (input_array);
}

void free_str_array(char **input_array)
{
    int count;

    count = 0;
    while (input_array[count])
    {
        free(input_array[count]);
        input_array[count] = NULL;
    }
    free(input_array);
    input_array = NULL;
}

int search_in_array(char **input_array, char* str, char sep)
{
    int count;

    count = 0;
    while (input_array[count])
    {
        if (sep)
        {
            if ((strcmp(str, ft_split(input_array[count], sep)[0])) == 0)
                return (count);
        }
        else
        {
            if ((strcmp(str, input_array[count])) == 0)
                return (count);
        }
        count++;
    }
    return (KO);
}

void display_array(char **input_array)
{
    int count;

    count = 0;
    while (input_array[count])
    {
        ft_putstr_fd(input_array[count], 1);
        write(1, "\n", 1);
        count++;
    }
}

char **extend_array(char **from_array, char **add_array, int from_len, int add_len)
{
    int count_from;
    int count_add;
    int index_from;
    int index_add;
    char **output_array;

    count_from = 0;
    count_add = 0;
    output_array = (char **)malloc(sizeof(char *) * (from_len + add_len + 1));
    while (from_array[count_from])
    {
        output_array[count_from] = ft_strdup(from_array[count_from]);
        count_from++;
    }
    output_array[count_from] = NULL;
    index_add = count_from;
    while (add_array[count_add])
    {
        if ((index_from = search_in_array(from_array, ft_split(add_array[count_add], '=')[0], '=')) >= 0)
        {
            free(output_array[index_from]);
            output_array[index_from] = add_array[count_add];
        }
        else
        {
            output_array[index_add] = add_array[count_add];
            index_add++;
        }
        count_add++;
    }
    output_array[count_from + count_add] = NULL;
    free_str_array(from_array);
    return (output_array);
}
