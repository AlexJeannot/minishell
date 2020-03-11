
#include "minishell.h"

static int	check_double_quote(char *str, int i)
{
	while (str[i] && str[i] != '"')
		i++;
	if (!str[i])
		exit(1);
	return (i);
}

static int	check_simple_quote(char *str, int i)
{
	while (str[i] && str[i] != ''')
		i++;
	if (!str[i])
		exit(1);
	return (i);
}

static int	spot_quote(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			i = check_double_quote(line, i);
		if (line[i] == ''')
			i = check_simple_quote(line, i);
		i++;
	}
}
