#include "../includes/exec.h"

void stdout_redirection(int input_fd[2])
{
    dup2(input_fd[1], STDOUT_FILENO);
}

int receive_pipe(int process_fd[2])
{
    struct	stat sb;
    struct	stat sb2;

    fstat(process_fd[0], &sb);
    printf("AVANT PIPE sb.st_size = %lld\n", sb.st_size);

    dup2(process_fd[0], STDIN_FILENO);

    fstat(process_fd[0], &sb2);
    printf("APRES PIPE sb.st_size = %lld\n", sb.st_size);
    return (0);
}