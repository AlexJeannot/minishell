#include "../includes/exec.h"

char *ft_construct_position(char *position)
{
    int length;
    int str_count;
    int border_size;
    char output_str[65];

    str_count = 0;
    length = ft_strlen(position);
    border_size = (64 - length - 2) / 2;
    while (str_count < border_size)
    {
        output_str[str_count] = '=';
        str_count++; 
    }
    output_str[str_count] = ' ';
    str_count++;
    output_str[str_count] = '\0';
    ft_strcat(output_str, position);
    length = ft_strlen(output_str);
    output_str[length] = ' ';
    length++;
    while (length < 64)
    {
        output_str[length] = '=';
        length++; 
    }
    output_str[length] = '\0';
    return (ft_strdup(output_str));
}

void ft_leaks(char *position)
{
    char str[4096];
    char *display_position;
    char *pid;

    display_position = ft_construct_position(position);
    if (position)
    {
        write(1, "\033[38;5;141m", 12);
        printf("\n\n%s\n", display_position);
        write(1, "\033[38;5;118m", 12);
        printf ("================================================================\n");
        free(display_position);
    }
    else
    {
        write(1, "\033[38;5;118m", 12);
        printf ("\n\n================================================================\n");
    }
    printf("========================= PROCESS %d ========================\n", getpid());
    printf ("================================================================\n\n");
    pid = ft_itoa(getpid());
    ft_strcpy(str, "leaks ");
    ft_strcat(str, pid);
    free_str(&pid);
    system(str);
    printf ("================================================================\n\n");
	write(1, "\033[0m", 4);
}