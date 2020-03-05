/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:21:45 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/05 17:03:38 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


pid_t ft_create_child(void)
{
    pid_t pid;

    pid = fork();
    return (pid);
}

void ft_path(char *cmd, char **env)
{
    int i;
    char *path;
    char **tab_path;
    char **tab_arg;
    char **final_tab;

    tab_arg = ft_split(cmd, ' ');
    i = 0;
    while (env[i] && (strcmp("PATH", ft_split(env[i], '=')[0])) != 0)
        i++;
    //printf("env[i] = %s\n", env[i]);
    tab_path = ft_split(ft_split(env[i], '=')[1], ':');
    //printf("tab_path[0] = %s\n", tab_path[0]);
    i = 0;
    while (tab_path[i])
    {
    //    printf("tab_path[i] = %s\n", tab_path[i]);
        i++;
    }
    final_tab = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (tab_path[i])
    {
    //    printf("tab_path[%d] = %s\n", i, tab_path[i]);
        path = (char *)malloc(sizeof(char) * (ft_strlen(tab_arg[0]) + ft_strlen(tab_path[i]) + 2));
    //    printf("MALLOC FAIT\n");
        path = strcat(path, tab_path[i]);
    //    printf("-----------------\n");
    //    printf("path 1 = %s\n", path);
        path[ft_strlen(tab_path[i])] = '/';
    //    printf("path 2 = %s\n", path);
        path = strcat(path, tab_arg[0]);
    //    printf("path 3 = %s\n", path);
    //    path[]
        final_tab[i] = path;
        i++;
    }
    final_tab[i] = NULL;

    i = 0;
    while (final_tab[i])
    {
        execve(final_tab[i], tab_arg, env);
        i++;
    }
}

void ft_new_env(char *path)
{
    int i;
    char *oldpwd;
    char *change_oldpwd;
    char *change_pwd;

    (void)path;

    i = 0;
    while (global_env[i])
    {
        if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
            oldpwd = ft_split(global_env[i], '=')[1];
        i++;
    }
    change_oldpwd = malloc(sizeof(char) * (ft_strlen(oldpwd) + 8));
    change_oldpwd[0] = 'O';
    change_oldpwd[1] = 'L';
    change_oldpwd[2] = 'D';
    change_oldpwd[3] = 'P';
    change_oldpwd[4] = 'W';
    change_oldpwd[5] = 'D';
    change_oldpwd[6] = '=';
    change_oldpwd = strcat(change_oldpwd, oldpwd);
    change_oldpwd[ft_strlen(oldpwd) + 7] = '\0';
//    printf("%s\n", change_oldpwd);

    change_pwd = malloc(sizeof(char) * (ft_strlen(path) + 5));
    change_pwd[0] = 'P';
    change_pwd[1] = 'W';
    change_pwd[2] = 'D';
    change_pwd[3] = '=';
    change_pwd = strcat(change_pwd, path);
    change_pwd[ft_strlen(path) + 4] = '\0';
//    printf("%s\n", change_pwd);

    i = 0;
    while (global_env[i])
    {
        if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
        {
            global_env[i] = change_pwd;
        }
        else if (strcmp(ft_split(global_env[i], '=')[0], "OLDPWD") == 0)
        {
            global_env[i] = change_oldpwd;
        }
        i++;
    }
}

void ft_cd(char *cmd, char **env)
{
    (void)env;
    char **tab_arg;
    char *path;
    char **tab_path;
    int i;
    int n;
    int a;
    int s;

    tab_arg = ft_split(cmd, ' ');
    if (tab_arg[1] == NULL)
        path = "/Users/ajeannot";
    else if (strcmp(tab_arg[1], "..") == 0)
    {
        i = 0;
        while (global_env[i])
        {
            if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
            {
                tab_path = ft_split(ft_split(global_env[i], '=')[1], '/');
                n = 0;
                s = 0;
                while (tab_path[n])
                {
                    s += ft_strlen(tab_path[n]);
                    n++;
                }
            //    printf("s = %d\n", s);
            //    printf("n = %d\n", n);
                a = 0;
                path = malloc(sizeof(char) * (s + (n - 1) + 1));
                while (a < n - 1)
                {
                    //printf("PATH INTER 1 = %s\n", path);
                    path = strcat(path, "/");
                //    printf("PATH INTER 2 = %s\n", path);
                    path = strcat(path, tab_path[a]);
                    a++;
                //    printf("PATH INTER 3 = %s\n", path);
                }
                path = strcat(path, "\0");
            }
            i++;
        }
    }
    else
        path = tab_arg[1];

    printf("PATH = %s\n", path);

    chdir(path);
    ft_new_env(path);
}

char **ft_sort_env(void)
{
    char **sort_tab;
    char *tmp;
    int i;
    int j;

    i = 0;
    while (global_env[i])
        i++;
    sort_tab = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (global_env[i])
    {
        sort_tab[i] = ft_strdup(global_env[i]);
        i++;
    }
    sort_tab[i] = NULL;

    i = 0;
    while (sort_tab[i])
    {
        j = i;
        while (sort_tab[j + 1])
        {
            if ((strcmp(sort_tab[j], sort_tab[j + 1])) > 0)
            {
                tmp = sort_tab[j];
                sort_tab[j] = sort_tab[j + 1];
                sort_tab[j + 1] = tmp;
                j = i;
            }
            else
                j++;
        }
        i++;
    }
    return (sort_tab);

}

int find_before(char *str, char to_find, char end)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == to_find)
            return (1);
        else if (str[i] == end)
            return (0);
    }
    return (0);
}

int find_var(char* arg)
{
    int i;

    i = 0;
    printf("ENTREE FCT\n");
    while(global_env[i])
    {
        if (strcmp(&arg[1], ft_split(global_env[i], '=')[0]) == 0)
            return (i);
        i++;
    }
    printf("SORTIE FCT\n");
    return (-1);
}

void ft_export(char *args)
{
    int i;
    int j;
    int e;
    int pass;
    int ret;
    int index;
    char* var;
    char **tab_args;
    char **sort_env;
    //char **tab_var;
    char **add_args;
    char **new_env;

    (void)args;

    i = 0;
    tab_args = ft_split(args, ' ');
    sort_env = ft_sort_env();
    i = 0;

    j = 0;
    while (tab_args[j])
        j++;
    add_args = malloc(sizeof(char *) * j);
    //printf("tab_args[1] = %s\n", tab_args[1]);
    if (tab_args[1] && tab_args[1][0] == '$' && find_var(tab_args[1]) != -1)
    {
        printf("ERROR\n");
    }
    else if (!(tab_args[1]) || tab_args[1][0] == '$' || tab_args[1][0] == '#')
    {
    //    printf("ENTREE\n");
        while (sort_env[i])
        {
            ft_putstr_fd(sort_env[i], 1);
            write(1, "\n", 1);
            i++;
        }
    }
    else
    {
    //    printf("LALA\n");
        i = 1;
        while (tab_args[i])
        {
            if ((tab_args[i][0] >= 65 && tab_args[i][0] >= 90) || (tab_args[i][0] >= 97 && tab_args[i][0] >= 122)
            || tab_args[i][0] == 92 || tab_args[i][0] >= 95)
            {
                printf("ENTREE DEBUT SET\n");
                if ((car_in_str(tab_args[i], '=') == -1))
                {
                    printf("ENTREE SANS =\n");
                    var = malloc(sizeof(char) * (ft_strlen(tab_args[i]) + 4));
                    var = strcat(var, tab_args[i]);
                    var = strcat(var, "=\'\'");
                }
                else if ((special_car_in_str(tab_args[i])) == -1)
                {
                    var = malloc(sizeof(char) * (ft_strlen(tab_args[i]) + 1));
                    var = strcat(var, tab_args[i]);
                }
                else if ((ret = special_car_in_str(tab_args[i])) != -1)
                {
                    printf("RET = %d\n", ret);
                    var = malloc(sizeof(char) * (ft_strlen(tab_args[i]) + 3));
                    j = 0;
                    e = 0;
                    pass = 0;
                    while (tab_args[i][j])
                    {
                        if (tab_args[i][j] && !(pass) && tab_args[i][j - 1] == '=')
                        {
                            var[e] = '\'';
                            pass = 1;
                            e++;
                        }
                        var[e] = tab_args[i][j];
                        e++;
                        j++;
                    }
                    var[e] = '\'';
                    var[e + 1] = '\0';
                }

                printf("Var = %s\n", var);

                add_args[i - 1] = var;
            }
            i++;
        }


        j = 0;
        while (sort_env[j])
            j++;
        new_env = malloc(sizeof(char *) * (j + i));
        j = 0;
        while (sort_env[j])
        {
            new_env[j] = sort_env[j];
            j++;
        }
        i = 0;
        while (add_args[i])
        {

            if ((index = elem_in_tab(global_env, ft_split(add_args[i], '=')[0], '=')) >= 0)
            {
                new_env[index] = add_args[i];
            }
            else
                new_env[j] = add_args[i];
            i++;
            j++;
        }

        global_env = new_env;

    }
//    printf("SORTIE EXPORT\n");
}

void ft_unset(char *args)
{
    int i;
    int j;
    int h;
    int ret;
    int to_delete;
    char **tab_args;
    char **new_env;
    int *tab_index;

    tab_args = ft_split(args, ' ');
    i = 1;
    while (tab_args[i])
    {
        i++;
    }
    tab_index = malloc(sizeof(int) * (i + 1));
    i = 0;
    j = 0;
    while (tab_args[i])
    {
        if ((ret = elem_in_tab(global_env, tab_args[i], '=')) >= 0)
        {
            tab_index[j] = ret;
            j++;
        }
        i++;
    }
    tab_index[j] = -1;
    i = 0;
    while (global_env[i])
    {
        i++;
    }
    new_env = malloc(sizeof(char *) * (i - j + 1));
    j = 0;
    i = 0;
    while (global_env[i])
    {
        h = 0;
        to_delete = 0;
        while (tab_index[h] != -1)
        {
            if (tab_index[h] == i)
                to_delete = 1;
            h++;
        }
        if (to_delete == 0)
        {
            new_env[j] = global_env[i];
            j++;
        }
        i++;
    }
    global_env = new_env;
}

void ft_exit(void)
{
    exit(0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    char *line;
    char *cmd;
    char *dir;
    char **tab_dir;
    int i;
    int n;

    global_env = env;
//    export = ft_sort(env);
    while (1)
    {

        /*AFFICHAGE PROMPT*/
        printf("\033[38;5;208m");
        fflush(stdout);
        i = 0;
        while (global_env[i])
        {
            if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
            {
                tab_dir = ft_split(ft_split(global_env[i], '=')[1], '/');
                n = 0;
                while (tab_dir[n])
                    n++;
                dir = tab_dir[n - 1];
            }
            i++;
        }
        write(1, dir, ft_strlen(dir));
        write(1, " ", 1);
        printf("\033[38;5;196m");
        fflush(stdout);
        write(1, "}> ", 3);
        printf("\033[0m");
        fflush(stdout);

        /*RECUPERATION INPUT*/
        get_next_line(0, &line);
        cmd = ft_split(line, ' ')[0];

        /*TRAITEMENT*/
        if (ft_create_child() == 0)
        {
        //    printf("\n----- ENTREE CHILD -----\n");
        /*    i = 0;
            while (global_env[i])
            {
                if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
                    printf("TEST = %s\n", global_env[i]);
                else if (strcmp(ft_split(global_env[i], '=')[0], "OLDPWD") == 0)
                    printf("TEST = %s\n", global_env[i]);
                i++;
            }
            printf("----- FIN ENTREE CHILD -----\n");*/
            if (strcmp(cmd, "pwd") == 0 || strcmp(cmd, "echo") == 0 || strcmp(cmd, "env") == 0)
                ft_path(line, global_env);
            else if (strcmp(cmd, "cd") == 0)
                ft_cd(line, global_env);
            else if (strcmp(cmd, "export") == 0)
                ft_export(line);
            else if (strcmp(cmd, "unset") == 0)
                ft_unset(line);
            /*printf("----- SORTIE CHILD -----\n");
            i = 0;
            while (global_env[i])
            {
                if (strcmp(ft_split(global_env[i], '=')[0], "PWD") == 0)
                    printf("TEST = %s\n", global_env[i]);
                else if (strcmp(ft_split(global_env[i], '=')[0], "OLDPWD") == 0)
                    printf("TEST = %s\n", global_env[i]);
                i++;
            }
            printf("----- FIN SORTIE CHILD -----\n\n");*/
        }
        else
        {
            if (strcmp(cmd, "exit") == 0)
                ft_exit();
            wait(NULL);
        }
    }
}
