#include "../includes/exec.h"


int    check_rdo_exec(t_list *lst)
{
    int count;
    int file_fd;

    count = 0;
    if (lst->rdo_type != 0)
    {
        while (lst->rdo_filetab[count])
        {
            if ((file_fd = open(lst->rdo_filetab[count], O_RDONLY)) == -1)
                return (count);
            count++;
        }
    }
    return (-1);
}

int set_redirection(t_list *lst, int fd[2])
{
    int count;
    int fd_file;
    int ret_check;
    int status;

    count = 0;
    status = 0;
    if ((ret_check = check_rdo_exec(lst)) != -1)
    {
        if (lst->rdc_filetab)
            while (lst->rdc_filetab[count] && lst->rdc_index[count] < lst->rdo_index[ret_check])
            {
                fd_file = open(lst->rdc_filetab[count], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
                close(fd_file);
                count++;
            }
        display_error(lst->rdo_filetab[ret_check], NULL);
    }
    while (lst->rdc_filetab[count])
    {
        open(lst->rdc_filetab[count], O_CREAT, S_IRWXU);
        count++;
    }
    dup2(fd[1], STDOUT_FILENO);
    status = exec_instructions(lst);
    return (status);
}

void    receive_redirection(t_list *lst, int fd[2])
{
    int     file_fd;
    int		ret;
    int     ret_check;
    int     error_index;
    int     file_index;
    char    buf[101];
    char    *str;
    struct	stat sb;

    str = NULL;
    ret_check = 0;
    error_index = 0;
    file_index = 0;
    if ((ret_check = check_rdo_exec(lst)) != -1)
    {
        error_index = lst->rdo_index[ret_check];
        file_index = lst->rdc_index[int_array_length(lst->rdc_index) - 1];
    }
    if (file_index <= error_index)
    {
        if (lst->rdc_type == 1)
            file_fd = open(lst->rdc_filename, O_WRONLY | O_TRUNC);
        else
            file_fd = open(lst->rdc_filename, O_WRONLY | O_APPEND);
        if (file_fd != -1)
        {
            fstat(fd[0], &sb);
            if (sb.st_size > 0)
            {
                while ((ret = read(fd[0], buf, 100)) > 0)
                {
                    buf[ret] = '\0';
                    str = ft_join(str, buf, ft_len(str), ft_len(buf));
                    if (ret < 100)
                            break ;
                }
            }
            write(file_fd, str, ft_len(str));
        }
    }
}
