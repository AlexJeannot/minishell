/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup_shlvl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:09:42 by ajeannot          #+#    #+#             */
/*   Updated: 2020/06/17 14:34:58 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	free_shlvl(char *shlvl_nb, char *shlvl_str, int shlvl_index)
{
	free_str(&global_env[shlvl_index]);
	free_str(&shlvl_nb);
	free_str(&shlvl_str);
}

void	incr_shlvl(int shlvl_index, int shlvl, char *shlvl_str, char *shlvl_nb)
{
	int		count;
	char	*shlvl_export;

	count = 0;
	if (shlvl_str[count] == 43 || shlvl_str[count] == 45)
		count++;
	while (shlvl_str[count] && shlvl_str[count] > 47 && shlvl_str[count] < 58)
	{
		shlvl = (shlvl * 10) + (shlvl_str[count] - 48);
		count++;
	}
	if (shlvl_str[count] != '\0')
		shlvl = 1;
	else if (shlvl_str[0] == 45)
		shlvl = 0;
	else
		shlvl++;
	shlvl_nb = ft_itoa(shlvl);
	if (!(shlvl_export = (char *)malloc(sizeof(char)
					* (ft_strlen(shlvl_nb) + 7))))
		ft_error('\0', "Malloc", NULL);
	ft_strcpy(shlvl_export, "SHLVL=");
	ft_strcat(shlvl_export, shlvl_nb);
	free_shlvl(shlvl_nb, shlvl_str, shlvl_index);
	global_env[shlvl_index] = shlvl_export;
}

void	setup_shlvl(void)
{
	int		shlvl_index;
	int		shlvl_final;
	char	*shlvl_str;
	char	*shlvl_nb;

	if ((shlvl_str = get_env_value("SHLVL")) == NULL)
		global_env = extend_array_str(global_env,
				"SHLVL=1", str_array_length(global_env));
	else
	{
		shlvl_final = 0;
		shlvl_nb = NULL;
		shlvl_index = search_in_array(global_env, "SHLVL", '=');
		incr_shlvl(shlvl_index, shlvl_final, shlvl_str, shlvl_nb);
	}
}
