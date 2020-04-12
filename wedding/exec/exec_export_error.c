#include "../includes/exec.h"

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

int display_invalid_export(char *str, int type)
{
    write(2, "Minishell: export: ", 19);
    write(2, "`", 1);
    if (!(type))
    {
        write(2, str, ft_strlen(str));
        write(2, "': not a valid identifier\n", 26);
    }
    if (type)
    {
        write(2, str, ft_strlen(str));
        write(2, "': not a valid value\n", 21);
    }
    return (1);
}

int verify_exported_var(char **input_array)
{
    int array_count;
    int equal_index;
    int     status;
    char    **split_result;

    array_count = 0;
    while (input_array[array_count])
    {
        split_result = ft_split(input_array[array_count], '=');
        if (is_valid_var(split_result[0]) == -1)
            status = display_invalid_export(split_result[0], 0);
        else if ((equal_index = find_car(input_array[array_count], '=')) != -1 && is_valid_value(&input_array[array_count][equal_index]) == -1)
            status = display_invalid_export(&input_array[array_count][equal_index], 1);
        array_count++;
    }
    free_str_array(split_result);
    return (status);
}