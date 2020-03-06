/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:08:28 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:36 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **sort_env(void)
{
    char **new_env;

    new_env = duplicate_array(global_env, '\0');
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

    count = 0;
    str_cmp = ft_split(str, '=')[0];

    while (init_env_var[count])
    {
        if (strcmp(init_env_var[count], str_cmp) == 0)
            return (KO);
        count++;
    }
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


void ft_export(char *args)
{
    int count;
    int equal_index;
    int args_len;
    char *var;
    char **tab_args;
    char **add_args;
    char **sorted_env;

    tab_args = ft_split(args, ' ');
    args_len = array_length(tab_args);
    add_args = malloc(sizeof(char *) * args_len);
    if (tab_args[1] && tab_args[1][0] == '$' && is_init_var(&tab_args[1][1]))
        printf("EXPORT PATH ERROR\n");
    else if (!(tab_args[1]) || tab_args[1][0] == '$' || tab_args[1][0] == '#')
    {
        count = 0;
        sorted_env = sort_env();
        display_array(sorted_env);
        free_str_array(sorted_env);
    }
    else
    {
        count = 1;
        while (tab_args[count])
        {
            /* Vérification si nom de variable OK */
            if (is_valid_var(tab_args[count]) == -1)
                printf("EXPORT VARIABLE ERROR\n");
            /* Vérification si valeur de variable et si cette valeur est OK */
            if ((equal_index = find_car(tab_args[count], '=')) != -1 && is_valid_value(&tab_args[count][equal_index]) == -1)
                printf("EXPORT VALUE ERROR\n");
            /* Si pas de valeur lors de l'export */
            if (find_car(tab_args[count], '=') == -1)
            {
                var = malloc(sizeof(char) * (ft_strlen(tab_args[count]) + 4)); // Malloc taille de la string + 4 pour =''\0
                var = ft_strcat(var, tab_args[count]); // Concaténation de la string allouée avec le nom de la variable
                var = ft_strcat(var, "=\'\'"); // Concaténation du nom de la variable avec =''\0
            }
            /*Si valeur avec caractère spécial */
            else if (find_special_car(&tab_args[count][equal_index + 1]) == -1)
            {
                var = malloc(sizeof(char) * (ft_strlen(tab_args[count]) + 3)); // Malloc taille de la string + 3 pour '' et \0
                var = ft_strncat(var, tab_args[count], equal_index + 1); // Concaténation de la string allouée avec le nom de la variable jusqu'au =
                var[equal_index + 1] = '\''; // Ajout premier '
                var = ft_strcat(var, &tab_args[count][equal_index] + 1);
                var[ft_strlen(var)] = '\''; // Ajout second '
                var[ft_strlen(var)] = '\0';
            }
            /* Autrement duplication */
            else
                var = ft_strdup(tab_args[count]);

            /* Ajout de la variable a exporter dans un tableau */
            add_args[count - 1] = var;
            count++;
        }
        add_args[count - 1] = NULL;
        global_env = extend_array(global_env, add_args, array_length(global_env), array_length(add_args));
    }
}
