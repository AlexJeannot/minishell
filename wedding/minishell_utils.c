#include "./includes/exec.h"

void display_prompt(void)
{
    char *dir;
    char **split_result_1;
    char **split_result_2;

    split_result_1 = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
    split_result_2 = ft_split(split_result_1[1], '/');
    dir = split_result_2[str_array_length(split_result_2) - 1];
    write(1, "\033[38;5;208m", 12);
    write(1, dir, ft_strlen(dir));
    write(1, " ", 1);
    write(1, "\033[38;5;196m", 12);
    write(1, "}> ", 3);
    write(1, "\033[0m", 4);
    free_str_array(split_result_1);
    free_str_array(split_result_2);
}

int exec_instructions(t_list *lst)
{
    int status;

    status = 0;
    if (ft_strcmp(lst->cmd, "pwd") == 0 || ft_strcmp(lst->cmd, "echo") == 0 || ft_strcmp(lst->cmd, "env") == 0)
        ft_builtins(lst, lst->cmd, lst->raw);
    else if (ft_strcmp(lst->cmd, "cd") == 0)
        ft_cd(lst->arg);
    else if (ft_strcmp(lst->cmd, "export") == 0)
        status = ft_export(lst->arg);
    else if (ft_strcmp(lst->cmd, "unset") == 0)
        status = ft_unset(lst->arg);
    else if (ft_strcmp(lst->cmd, "exit") != 0)
        ft_program(lst, lst->cmd, lst->raw);
    return (status);
}

void exec_child(t_list *lst, int exit_status, int fd[2])
{
    replace_exit_status(lst, exit_status);
    if (lst->rdc_type != 0 || lst->rdo_type != 0)
        exit_status = set_redirection(lst, fd);
    else if (lst->pipe == 1)
        exit_status = set_pipe(lst, fd);
    else
    {
        exit_status = exec_instructions(lst);
        send_env(fd);
    }
    exit(exit_status);
}

int exec_father(t_list *lst, int exit_status, int fd[2])
{
    int ret_child;

    waitpid(child_pid, &ret_child, 0);
    if (WIFEXITED(ret_child))
        exit_status = WEXITSTATUS(ret_child);
    if (lst->rdc_type != 0)
        receive_redirection(lst, fd);
    else if (lst->pipe == 1)
        exit_status = receive_pipe(fd);
    else if (exit_status == 0)
    {
        if (env_need_update(lst->cmd))
            receive_env(fd);
    }
    if (ft_strcmp(lst->cmd, "exit") == 0)
        ft_exit_2(NULL, 0);
    filtered_env = filter_env(global_env, filtered_env);
    return (exit_status);
}

int exec_command_line(int exit_status, int fd[2], char *line)
{
    parsing(line);
    while (lst)
    {
        setup_command();
        if (child_pid == 0)
            exec_child(lst, exit_status, fd);
        else
            exit_status = exec_father(lst, exit_status, fd);
        lst = lst->next;
    }
    return (exit_status);
}

void ft_exit_2(char **free_split, int status)
{
    if (free_split)
        free_str_array(free_split);
    clear_lst();
    free_str_array(filtered_env);
    free_str_array(global_env);

    system("leaks minishell");
    exit(status);
}