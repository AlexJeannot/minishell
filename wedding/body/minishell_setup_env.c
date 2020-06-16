#include "../includes/exec.h"

void setup_oldpwd(void)
{
    int oldpwd_index;

    if ((oldpwd_index = search_in_array(global_env, "OLDPWD", '=')) == -1)
        global_env = extend_array_str(global_env, "OLDPWD", str_array_length(global_env));
/*
    {
        free_str(&global_env[oldpwd_index]);
        global_env[oldpwd_index] = ft_strdup("OLDPWD"); 
    }
*/
}

void setup_pwd(void)
{
    char set_pwd[4096];

    if (search_in_array(global_env, "PWD", '=') == -1)
    {
        getcwd(set_pwd, 4096);
        update_pwd(-1, set_pwd);
    }
    pwd_path = get_env_value("PWD");
    pwd_check = 0;
}

void setup_var(char *exe)
{
    char *set_var;

    set_var = NULL;
    if (search_in_array(global_env, "_", '=') == -1)
    {
        set_var = (char *)malloc(sizeof(char) * (ft_strlen(pwd_path) + ft_strlen(exe) + 3));
        ft_strcpy(set_var, "_=");
        ft_strcat(set_var, pwd_path);
        ft_strcat(set_var, "/");
        ft_strcat(set_var, exe);
        global_env = extend_array_str(global_env, set_var, str_array_length(global_env));
    }
}

void setup_env(char **argv, char **env, int *exit_status)
{
    errno = 0;
    child_pid = -1;
    global_env = duplicate_array(env, NULL, '\0');
    setup_oldpwd();
    setup_shlvl();
    setup_pwd();
    setup_var(argv[0]);
    *exit_status = 0;
    filtered_env = filter_env(global_env, NULL);
    signal(SIGINT, signal_manager);
    signal(SIGQUIT, signal_manager);
}