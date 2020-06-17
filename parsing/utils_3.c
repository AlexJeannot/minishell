/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouleng <cbouleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:58:01 by cbouleng          #+#    #+#             */
/*   Updated: 2020/05/27 18:58:02 by cbouleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int		ft_envcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && !s2[i])
		return (1);
	return (0);
}

int		is_env(char *str, int j)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_env_name_2check(str, j);
	while (global_env[i])
	{
		if (ft_envcmp(global_env[i], tmp))
		{
			free_str(&tmp);
			return (1);
		}
		i++;
	}
	free_str(&tmp);
	return (0);
}

int		quote_stop(char *str, int j)
{
	int	k;

	k = j;
	while (str[j] != '\'' && str[j])
		j--;
	while (str[k] != '\'' && str[k])
		k++;
	if (str[k] == '\'' && str[j] == '\'')
		return (1);
	return (0);
}
