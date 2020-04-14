#include "../includes/exec.h"

int length_with_status(char *input_str, int status)
{
    int total;

    total = ft_strlen(input_str) - 2;
    total += ft_strlen(ft_itoa(status));
    total++;
    return (total);
}

char *create_str_with_exit(char *input_str, int index, int status)
{
    int output_length;
    char *output_str;

    output_length = length_with_status(input_str, status);
    if (!(output_str = (char *)malloc(sizeof(char) * output_length)))
        display_error(NULL, NULL);
    output_str = ft_strncat(output_str, input_str, index);
    output_str = ft_strcat(output_str, ft_itoa(status));
    output_str = ft_strcat(output_str, &input_str[index + 2]);
    return(output_str);
}

void replace_exit_status(int status)
{
    int array_count;
    int str_count;
    char **raw_array;
	char*	map;

    array_count = 0;
    raw_array = lst->raw;
    while (raw_array[array_count])
    {
        str_count = 0;
        while (raw_array[array_count][str_count])
        {
			map = map_quote(raw_array[array_count], 0);
            if (raw_array[array_count][str_count] == '$' && map[str_count] != '1' && !is_esc(raw_array[array_count], str_count)
				&& raw_array[array_count][str_count + 1] == '?')
            {
                raw_array[array_count] = create_str_with_exit(raw_array[array_count], str_count, status);
                if (array_count == 0)
                    lst->cmd = ft_strdup(raw_array[array_count]);
                else
                    lst->arg[array_count - 1] = ft_strdup(raw_array[array_count]);
                str_count = 0;
            }
            else
                str_count++;
        }
        array_count++;
    }
}
