#include "../includes/exec.h"

int    check_rdo_exec(void)
{
    int count;
    int file_fd;

    count = 0;
    if (lst->rdo_type != 0)
    {
        while (lst->rdo_filetab[count])
        {
            if ((file_fd = open(lst->rdo_filetab[count], O_RDONLY)) == -1)
            {
                close(file_fd);
                return (count);
            }
            count++;
        }
    }
    return (-1);
}

void set_rdo(void)
{
    int count;
    int fd_file;
    int ret_check;

    count = 0;
    if ((ret_check = check_rdo_exec()) != -1)
    {
        if (lst->rdc_filetab)
            while (lst->rdc_filetab[count] && lst->rdc_index[count] < lst->rdo_index[ret_check])
            {
                fd_file = open(lst->rdc_filetab[count], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
                close(fd_file);
                count++;
            }
        ft_error('\0', lst->rdo_filetab[ret_check], NULL);
    }
    if (lst->rdc_filetab)
        while (lst->rdc_filetab[count])
        {
            fd_file = open(lst->rdc_filetab[count], O_CREAT, S_IRWXU);
            close(fd_file);
            count++;
        }
}

void write_in_file(int redirection_fd[2])
{
    int file_fd;
    char    *file_str;

    file_str = NULL;
    if (lst->rdc_type == 1)
        file_fd = open(lst->rdc_filename, O_WRONLY | O_TRUNC);
    else
        file_fd = open(lst->rdc_filename, O_WRONLY | O_APPEND);
    if (file_fd != -1)
    {
        file_str = read_from_fd(redirection_fd);
        write(file_fd, file_str, ft_len(file_str));
        free_str(&file_str);
    }
    close(file_fd);
}

void    receive_redirection(int redirection_fd[2])
{
    int     ret_check;
    int     error_index;
    int     file_index;

    error_index = 0;
    file_index = 0;
    if ((ret_check = check_rdo_exec()) != -1)
    {
        error_index = lst->rdo_index[ret_check];
        file_index = lst->rdc_index[int_array_length(lst->rdc_index) - 1];
    }
    if (file_index <= error_index || ret_check == -1)
        write_in_file(redirection_fd);
}
