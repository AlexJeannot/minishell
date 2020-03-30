/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:08:28 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/09 19:45:17 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **sort_env(void)
{
    char **new_env;

    new_env = duplicate_array(global_env, NULL, '\0');
    new_env = sort_array(new_env);
    return (new_env);
}

int is_valid_var(char *str)
{
    int count;

    count = 0;
    while (str[count] && str[count] != '=')
    {
        if (str[count] < 'A'
        || (str[count] > 'Z' && str[count] < 'a'
        && str[count] != '\\' && str[count] < '_')
        || str[count] > 'z')
            return (KO);
        count++;
    }
    return (OK);
}

int is_valid_value(char *str)
{
    int count;

    count = 0;
    while (str[count] && str[count] != '=')
    {
        if (str[count] < '!' && str[count] == 127)
            return (KO);
        count++;
    }
    return (OK);
}

int is_init_var(char *str)
{
    int count;
    char *str_cmp;
    char **split_result;

    count = 0;
    split_result = ft_split(str, '=');
    str_cmp = split_result[0];

    while (init_env_var[count])
    {
        if (ft_strcmp(init_env_var[count], str_cmp) == 0)
        {
            free_str_array(split_result);
            return (KO);
        }
        count++;
    }
    free_str_array(split_result);
    return (OK);
}

int find_special_car(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (str[count] == '$' || str[count] == '\\'
        || str[count] == '=' || str[count] == '?'
        || str[count] == '[' || str[count] == ']'
        || str[count] == '{' || str[count] == '}'
        || str[count] == '~' || str[count] == '*'
        || str[count] == '#')
            return (KO);
        count++;
    }
    return (OK);
}


void ft_export(char **args)
{
    int count;
    int equal_index;
    int args_len;
    char *var;
    char **add_args;
    char **sorted_env;

    add_args = NULL;
    args_len = array_length(args);
    if (args[0] && args[0][0] == '$' && is_init_var(&args[0][1]))
        printf("EXPORT PATH ERROR\n");
    else if (!(args[0]) || args[0][0] == '$' || args[0][0] == '#')
    {
        count = 0;
        sorted_env = sort_env();
        display_array(sorted_env);
        free_str_array(sorted_env);
    }
    else
    {
        count = 0;
        add_args = malloc(sizeof(char *) * (args_len + 1));
        while (args[count])
        {
            /* Vérification si nom de variable OK */
            if (is_valid_var(args[count]) == -1)
                printf("EXPORT VARIABLE ERROR\n");
            /* Vérification si valeur de variable et si cette valeur est OK */
            if ((equal_index = find_car(args[count], '=')) != -1 && is_valid_value(&args[count][equal_index]) == -1)
                printf("EXPORT VALUE ERROR\n");
            /* Si pas de valeur lors de l'export */
            if (find_car(args[count], '=') == -1)
            {
                var = malloc(sizeof(char) * (ft_strlen(args[count]) + 4)); // Malloc taille de la string + 4 pour =''\0
                var = ft_strcat(var, args[count]); // Concaténation de la string allouée avec le nom de la variable
                var = ft_strcat(var, "=\'\'"); // Concaténation du nom de la variable avec =''\0
            }
            /*Si valeur avec caractère spécial */
            else if (find_special_car(&args[count][equal_index + 1]) == -1)
            {
                var = malloc(sizeof(char) * (ft_strlen(args[count]) + 3)); // Malloc taille de la string + 3 pour '' et \0
                var = ft_strncat(var, args[count], equal_index + 1); // Concaténation de la string allouée avec le nom de la variable jusqu'au =
                var[equal_index + 1] = '\''; // Ajout premier '
                var = ft_strcat(var, &args[count][equal_index] + 1);
                var[ft_strlen(var)] = '\''; // Ajout second '
                var[ft_strlen(var)] = '\0';
            }
            /* Autrement duplication */
            else
                var = ft_strdup(args[count]);

            /* Ajout de la variable a exporter dans un tableau */
            add_args[count] = var;
            count++;
        }
        add_args[count] = NULL;
        global_env = extend_array(global_env, add_args, array_length(global_env), array_length(add_args));
    }
    free_str_array(args);
    if (add_args)
        free_str_array(add_args);
//    printf("FIN FCT EXPORT\n");
}