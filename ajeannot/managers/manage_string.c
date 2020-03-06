/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 12:17:09 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/06 18:59:52 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_car(char *str, char c)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (str[count] == c)
            return (count);
        count++;
    }
    return (-1);
}

int ft_strlen(const char *str)
{
    int count;

    count = 0;
    if (str)
    {
        while (str[count])
            count++;
        return (count);
    }
    return (-1);
}

char	*ft_strdup(const char *s)
{
	int		size;
	int		cmp;
	char	*new_string;

	cmp = 0;
	size = ft_strlen(s);
	new_string = malloc(sizeof(char) * (size + 1));
	if (new_string == NULL)
		return (0);
	while (cmp < size)
	{
		new_string[cmp] = s[cmp];
		cmp++;
	}
	new_string[cmp] = '\0';
	return (new_string);
}

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
