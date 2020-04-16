#include "../includes/exec.h"


void display_exec(char *exec)
{
    write(1, exec, ft_strlen(exec));
    write(1, ": ", 2);
}

void ft_error(char symbol, char *cmd, char *msg)
{
    write(1, "Minishell: ", 11);
    if (cmd && !ft_strcmp(cmd, "rd"))
        ft_error_rd(msg, symbol);
    else
    {
        if (cmd)
            display_exec(cmd);
        if (msg)
            write(1, msg, ft_strlen(msg));
        else
            write(1, strerror(errno), ft_strlen(strerror(errno)));
    }
    write(1, "\n", 1);
    ft_exit(1);
}

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

void ft_exit(int status)
{
    free_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);
    free_str(&piped_str); 
	//ft_leaks("AT EXIT");
    exit(status);
}



