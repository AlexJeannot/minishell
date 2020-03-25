#include "minishell.h"

char*	output_filename(char** p_str)
{
	char*	rd;

	while (*p_str[i])
	{
		if (*p_str[i] == '>' && *p_str[i + 1] == '>')
			rd.type = 2;
		else if (*p_str[i] == '>')
			rd.type = 1;
		rd.filename = get_name(*p_str);
		i++;
	}
	return (rd);
}

char*	redirection(char** p_str)
{
	char*	rd;

	rd = output_filename(p_str);
	return (rd);
}
