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
                close_fd(file_fd);
                return (count);
            }
            count++;
        }
    }
    return (-1);
}

void manage_rdo_error(int ret_check)
{
    int count;
    int fd_file;

    count = 0;
    if (lst->rdc_filetab)
    {
        while (lst->rdc_filetab[count] && lst->rdc_index[count] < lst->rdo_index[ret_check])
        {
            fd_file = open(lst->rdc_filetab[count], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
            close_fd(fd_file);
            count++;
        }
        ft_error('\0', lst->rdo_filetab[ret_check], NULL);
    }
}

void create_file(void)
{
    int count;
    int fd_file;

    count = 0;
    if (lst->rdc_filetab)
    {
        while (lst->rdc_filetab[count])
        {
            fd_file = open(lst->rdc_filetab[count], O_CREAT, S_IRWXU);
            close_fd(fd_file);
            count++;
        }
    }
}

void red_stdout_in_file(void)
{
    int fd_file;

    if (lst->rdc_type == 1)
        fd_file = open(lst->rdc_filename, O_WRONLY | O_TRUNC);
    else
        fd_file = open(lst->rdc_filename, O_WRONLY | O_APPEND);
    dup2(fd_file, STDOUT_FILENO);
    close_fd(fd_file);
}

void manage_redirection(void)
{
    int ret_check;

    if ((ret_check = check_rdo_exec()) != -1)
        manage_rdo_error(ret_check);
    create_file();
    red_stdout_in_file();
}