/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:08:28 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/16 17:28:31 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int		export_without_args(char **input_array)
{
	if (!(input_array[0]) || input_array[0][0] == '#')
		return (1);
	if (input_array[0][0] == '$' && input_array[0][1] == '@')
		return (1);
	if (input_array[0][0] == '$' && is_valid_var(&input_array[0][1]) == 1)
		return (1);
	return (0);
}

int		add_exported_var(char *input_str, char **output_array, int add_count)
{
	char *add_var;

	add_var = ft_strdup(input_str);
	output_array[add_count] = add_var;
	add_count++;
	return (add_count);
}

char	**create_exported_var_array(char **input_array)
{
	int		array_count;
	int		add_count;
	char	**split_result;
	char	**output_array;

	array_count = 0;
	add_count = 0;
	if (!(output_array = malloc(sizeof(char *)
	* (str_array_length(input_array) + 1))))
		ft_error('\0', "Malloc", NULL, 1);
	while (input_array[array_count])
	{
		split_result = ft_split(input_array[array_count], '=');
		if (verify_exported_var(input_array[array_count]) == 0)
			add_count = add_exported_var(input_array[array_count]
			, output_array, add_count);
		free_str_array(split_result);
		array_count++;
	}
	output_array[add_count] = NULL;
	return (output_array);
}

int		ft_export(char **args)
{
	int		status;
	char	**add_array;

	status = 0;
	add_array = NULL;
	printf("-------- ARGS --------\n");
	display_str_array(args);
	printf("-------- ARGS --------\n");
	if (export_without_args(args))
		display_exported_env();
	else
	{
		printf("AVANT VERIFY EXPORTED\n");
		status = verify_exported_array(args);
		printf("APRES VERIFY EXPORTED\n");
		add_array = create_exported_var_array(args);
<<<<<<< HEAD
		printf("APRES create_exported_var_array\n");
		printf("-------- add_array --------\n");
		display_str_array(add_array);
		printf("-------- add_array --------\n");
		g_global_env = extend_array(g_global_env, add_array
		, str_array_length(g_global_env), str_array_length(add_array));
		printf("APRES extend_array\n");
=======
		g_global_env = extend_array(g_global_env, add_array
		, str_array_length(g_global_env), str_array_length(add_array));
>>>>>>> 43c1cd873d3b4546385fa225d35f1ee14f8ba7ab
	}
	free_str_array(add_array);
	printf("FIN FT EXPORT\n");
	return (status);
}
