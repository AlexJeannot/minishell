#include "../includes/exec.h"

char **duplicate_array(char **input_array, char **free_array, char sep)
{
    int count;
    int array_len;
    char **output_array;
    char **split_result;

    count = 0;
    array_len = str_array_length(input_array);
    output_array = (char **)malloc(sizeof(char *) * (array_len + 1));
    while (input_array[count])
    {
        if (sep)
        {
            split_result = ft_split(input_array[count], sep);
            output_array[count] = ft_strdup(split_result[0]);
            free_str_array(split_result);
        }
        else
            output_array[count] = ft_strdup(input_array[count]);
        count++;
    }
    output_array[count] = NULL;
    if (free_array)
        free_str_array(free_array);
    return (output_array);
}

char **sort_array(char **input_array)
{
    int array_count;
    int sort_count;
    char *str_tmp;

    array_count = 0;
    while (input_array[array_count])
    {
        sort_count = array_count;
        while (input_array[sort_count + 1])
        {
            if ((ft_strcmp(input_array[sort_count], input_array[sort_count + 1])) > 0)
            {
                str_tmp = input_array[sort_count];
                input_array[sort_count] = input_array[sort_count + 1];
                input_array[sort_count + 1] = str_tmp;
                sort_count = array_count;
            }
            else
                sort_count++;
        }
        array_count++;
    }
    return (input_array);
}

int search_in_array(char **input_array, char* str, char sep)
{
    int count;
    char **split_result;

    count = 0;
    while (input_array[count])
    {
        if (sep)
        {
            split_result = ft_split(input_array[count], sep);
            if ((ft_strcmp(str, split_result[0])) == 0)
            {
                free_str_array(split_result);
                return (count);
            }
            free_str_array(split_result);
        }
        else
        {
            if ((ft_strcmp(str, input_array[count])) == 0)
                return (count);
        }
        count++;
    }
    return (KO);
}

char **extend_array(char **from_array, char **add_array, int from_len, int add_len)
{
    int count_from;
    int count_add;
    int index_from;
    int index_add;
    char **output_array;
    char **split_result;

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
        split_result = ft_split(add_array[count_add], '=');
        if ((index_from = search_in_array(output_array, split_result[0], '=')) >= 0)
        {
            free(output_array[index_from]);
            output_array[index_from] = ft_strdup(add_array[count_add]);
        }
        else
        {
            output_array[index_add] = ft_strdup(add_array[count_add]);
            index_add++;
        }
        free(split_result);
        count_add++;
        output_array[count_from + count_add] = NULL;
    };
    free_str_array(from_array);
    return (output_array);
}

char **filter_env(char **input_array, char** free_array)
{
    int from_count;
    int add_count;
    char **output_array;

    from_count = 0;
    add_count = 0;
    if (!(output_array = (char **)malloc(sizeof(char *) * (str_array_length(input_array) + 1))))
        printf("MALLOC ERROR\n");
    while (input_array[from_count])
    {
        if (find_car(input_array[from_count], '=') != -1)
        {
            output_array[add_count] = ft_strdup(input_array[from_count]);
            add_count++;
        }
        from_count++;
    }
    output_array[add_count] = NULL;
    if (free_array)
        free(free_array);
    return (output_array);
}