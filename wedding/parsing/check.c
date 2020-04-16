#include "../includes/parsing.h"

char* map;

void	check_simple_quote(char* str)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '3')
		{
			i++;
			while (map[i] == '1')
				i++;
			if (map[i] != '3' || str[i] != '\'')
				ft_error('\0', NULL, "check_simple_quote failed");
		}
		i++;
	}
}

void	check_double_quote(char* str)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '4')
		{
			i++;
			while (map[i] == '2')
				i++;
			if (map[i] != '4' || str[i] != '"')
				ft_error('\0', NULL, "check_double_quote failed");
		}
		i++;
	}
}

void		check_bs(char* str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i >= 0)
	{
		if (str[i] == '\\' && (!str[i + 1] || str[i + 1] == ' ')
			&& map[i] == '0')
		{
			if (!is_esc(str, i))
				ft_error('\0', NULL, "check_bs failed");
			else
				return ;
		}
		i--;
	}
}

void	check_rdc(char* str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
				ft_error('>', "rd", "syntax error near unexpected symbol `");
			if (str[i] == '>' && str[i - 1] != '>' && str[i + 1] != '>')
			{
				j = i + 1;
				while (str[j] == ' ')
					j++;
				if (!is_name(str, j))
					ft_error(str[j], "rd", "syntax error near unexpected symbol `");
			}
			if (str[i] == '>' && str[i + 1] == '>' && str[i - 1] != '>')
			{
				j = i + 2;
				while (str[j] == ' ')
					j++;
				if (!is_name(str, j))
					ft_error(str[j], "rd", "syntax error near unexpected symbol `");
			}
		}
		i++;
	}

}

void	check_rdo(char* str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (map[i] == '0' && !is_esc(str, i))
		{
			if (str[i] == '<' && str[i + 1] == '<')
				ft_error('<', "rd", "syntax error near unexpected symbol `");
			if (str[i] == '<')
			{
				j = i + 1;
				while (str[j] == ' ')
					j++;
				if (!is_name(str, j))
					ft_error(str[j], "rd", "syntax error near unexpected symbol `");
			}
		}
		i++;
	}
}

void	check(char* line)
{
	map = map_quote(line, 0);
	check_simple_quote(line);
	check_double_quote(line);
	check_bs(line);
	check_rdc(line);
	check_rdo(line);
	free_str(&map);
}
