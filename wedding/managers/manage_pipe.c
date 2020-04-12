#include "../includes/exec.h"

int set_pipe(t_list *lst, int fd[2])
{
    int status;

    dup2(fd[1], STDOUT_FILENO);
    status = exec_instructions(lst);
    return (status);
}

int receive_pipe(int fd[2])
{
    int		ret;
    char    buf[101];
    struct	stat sb;

    fstat(fd[0], &sb);
    if (sb.st_size > 0)
    {
        while ((ret = read(fd[0], buf, 100)) > 0)
    	{
    		buf[ret] = '\0';
    		piped_str = ft_join(piped_str, buf, ft_len(piped_str), ft_len(buf));
            if (ret < 100)
                    break ;
    	}
    }
    return (0);
}