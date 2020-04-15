/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:47:48 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:35:40 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int is_builtins(char *cmd)
{
    if ((ft_strcmp(cmd, "echo") == 0)
        || (ft_strcmp(cmd, "pwd") == 0)
        || (ft_strcmp(cmd, "env") == 0))
        return (1);
    return (0);
}

char **build_exec_array(char *exec, char **path_array)
{
    int count;
    char *exec_path;
    char **exec_array;

    count = 0;
    if (!(exec_array = (char **)malloc(sizeof(char *) * (str_array_length(path_array) + 1))))
		ft_error('\0', "Malloc", NULL);
    while (path_array[count])
    {
        if (!(exec_path = (char *)malloc(sizeof(char) * (ft_strlen(exec) + ft_strlen(path_array[count]) + 2))))
		    ft_error('\0', "Malloc", NULL);
        ft_strcpy(exec_path, path_array[count]);
        ft_strcat(exec_path, "/");
        ft_strcat(exec_path, exec);
        exec_array[count] = exec_path;
        count++;
    }
    exec_array[count] = NULL;
    free_str_array(path_array);
    return (exec_array);
}

char **select_env(char *exec)
{
    if (ft_strcmp(exec, "env") == 0)
        return(filtered_env);
    else
        return(global_env);
}

char **add_file(char **input_array, char *file)
{
    char **output_array;

    if (!(output_array = (char**)malloc(sizeof(char *) * 3)))
		ft_error('\0', "Malloc", NULL);
    output_array[0] = ft_strdup(input_array[0]);
    output_array[1] = ft_strdup(file);
    output_array[2] = NULL;
    return (output_array);

}

char **setup_builtins(char *exec)
{
    int index_path;
    char **split_result;
    char **path_array;
    char **exec_array;
    
    index_path = search_in_array(global_env, "PATH", '=');
    split_result = ft_split(global_env[index_path], '=');
    path_array = ft_split(split_result[1], ':');
    exec_array = build_exec_array(exec, path_array);
    free_str_array(split_result);
    return (exec_array);
}

void ft_builtins(char *exec, char **args)
{
    int count;
    int ret_exec;
    char **exec_array;
    char **used_env;

    count = 0;
    exec_array = setup_builtins(exec);
    used_env = select_env(exec);
    if ((str_array_length(args) == 1 && ft_strcmp(args[0], "cat")) == 0 && lst->rdo_filename)
        args = add_file(args, lst->rdo_filename);
    while (exec_array[count])
    {
        ret_exec = execve(exec_array[count], args, used_env);
        count++;
    }
    if (ret_exec == -1)
        ft_error('\0', exec, "command not found");
}
