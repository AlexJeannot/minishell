/**
 * @Author: Alexandre Jeannot <ajeannot>
 * @Date:   2020-03-04T13:27:44+01:00
 * @Email:  lalal@gmail.com
 * @Filename: fct_annexes.c
 * @Last modified by:   ajeannot
 * @Last modified time: 2020-03-05T15:09:29+01:00
 */



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_annexes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannot <ajeannot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:08:17 by ajeannot          #+#    #+#             */
/*   Updated: 2020/03/05 15:09:29 by ajeannot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "test.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (str[i])
            i++;
        return (i);
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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	cmp;

	cmp = 0;
	while (s[cmp])
	{
		ft_putchar_fd(s[cmp], fd);
		cmp++;
	}
}

int car_in_str(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

int special_car_in_str(char *str)
{
    int i;
    int j;
    int tab_car[9];

    tab_car[0] = 42;    //*
    tab_car[1] = 61;      //=
    tab_car[2] = 63;      //?
    tab_car[3] = 91;      //[
    tab_car[4] = 93;      //]
    tab_car[5] = 123;      //{
    tab_car[6] = 125;      //}
    tab_car[7] = 126;      //~
    tab_car[8] = 0;      //NULL

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    i++;
    while (str[i])
    {
        j = 0;
        while (tab_car[j])
        {
            if (str[i] == tab_car[j])
                return (i);
            j++;
        }
        i++;
    }
    return (-1);
}

int elem_in_tab(char **tab_input, char* str, char sep)
{
    int i;

    i = 0;
    while (tab_input[i])
    {
        if (sep)
        {
            if ((strcmp(str, ft_split(tab_input[i], sep)[0])) == 0)
                return (i);
        }
        else
        {
            if ((strcmp(str, tab_input[i])) == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}
