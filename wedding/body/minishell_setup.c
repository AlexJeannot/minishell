#include "../includes/exec.h"

void signal_manager(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        if (child_pid == -1)
            exec_prompt();
    }
    if (sig == SIGQUIT)
    {
        if (child_pid && child_pid > 0)
        {
            write(1, "Quit: 3\n", 8);
            kill(child_pid, SIGKILL);
        }
    }
}

void incr_shlvl(int shlvl_index, int shlvl_final, char *shlvl_str, char *shlvl_nb)
{
    int count;
    char *shlvl_export;
    
    count = 0;
    if (shlvl_str[count] == 43 || shlvl_str[count] == 45)
        count++;
    while (shlvl_str[count] && shlvl_str[count] > 47 && shlvl_str[count] < 58)
    {
        shlvl_final = (shlvl_final * 10) + (shlvl_str[count] - 48);
        count++;
    }
    if (shlvl_str[count] != '\0')
        shlvl_final = 1;
    else if (shlvl_str[0] == 45)
        shlvl_final = 0;
    else
        shlvl_final++;
    shlvl_nb = ft_itoa(shlvl_final);
    if (!(shlvl_export = (char *)malloc(sizeof(char) * (ft_strlen(shlvl_nb) + 7))))
        ft_error('\0', "Malloc", NULL);
    ft_strcpy(shlvl_export, "SHLVL=");
    ft_strcat(shlvl_export, shlvl_nb);
    free_str(&global_env[shlvl_index]);
    free_str(&shlvl_nb);
    free_str(&shlvl_str);
    global_env[shlvl_index] = shlvl_export;
}

void setup_shlvl(void)
{
    int shlvl_index;
    int shlvl_final;
    char *shlvl_str;
    char *shlvl_nb;
 
    if ((shlvl_str = get_env_value("SHLVL")) == NULL)
        global_env = extend_array_str(global_env, "SHLVL=1", str_array_length(global_env));
    else
    {
        shlvl_final = 0;
        shlvl_nb = NULL;
        shlvl_index = search_in_array(global_env, "SHLVL", '=');
        incr_shlvl(shlvl_index, shlvl_final, shlvl_str, shlvl_nb);
    }
}

void setup_env(char **env, int *exit_status)
{
    int oldpwd_index;
    char set_pwd[4096];

    errno = 0;
    child_pid = -1;
    global_env = duplicate_array(env, NULL, '\0');
    if ((oldpwd_index = search_in_array(global_env, "OLDPWD", '=')) >= 0)
    {
        free_str(&global_env[oldpwd_index]);
        global_env[oldpwd_index] = ft_strdup("OLDPWD"); 
    }
    else
        global_env = extend_array_str(global_env, "OLDPWD", str_array_length(global_env));
    setup_shlvl();
    if (search_in_array(global_env, "PWD", '=') == -1)
    {
        getcwd(set_pwd, 4096);
        update_pwd(-1, set_pwd);
    }
    pwd_path = get_env_value("PWD");
    filtered_env = filter_env(global_env, NULL);
    pwd_check = 0;
    *exit_status = 0;
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}

void setup_command(int exit_status)
{
    replace_exit_status(exit_status);
	get_dollar();
    clear_before_exec();
}

int *setup_pipe_and_process(int exit_status, int *read_fd)
{
    int prev_pipe;
    int prev_fd;
    int p_fd[2];
    int pwd_fd[2];

    prev_fd = -1;
    prev_pipe = -1;
    lst_free = lst;
    p_fd[0] = -1;
    pwd_fd[0] = -1;
	while (lst)
	{

        if (prev_pipe == 0)
            exit_status = wait_for_child(exit_status, p_fd[0], pwd_fd[0]);
        if (lst->cmd && ft_strcmp(lst->cmd, "exit") == 0 && lst->pipe != 1 && prev_pipe != 1)
            ft_exit(0);
        if ((pipe(p_fd)) == -1)
            ft_error('\0', "Pipe", NULL);
        if ((pipe(pwd_fd)) == -1)
            ft_error('\0', "Pipe", NULL);
        if ((child_pid = fork()) == -1)
            ft_error('\0', "Fork", NULL);
        if (child_pid > 0)
            setup_parent(&prev_fd, &prev_pipe, p_fd, pwd_fd); 
        else
        {
            setup_child(prev_fd, prev_pipe, p_fd, pwd_fd);
            exec_child(prev_pipe, exit_status, p_fd[1], pwd_fd[1]);
        }
	}
    read_fd[0] = p_fd[0];
    read_fd[1] = pwd_fd[0];
    return (read_fd);
}
