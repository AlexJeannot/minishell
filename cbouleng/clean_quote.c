#include "minishell.h"

int		to_del_quote(int i, int j, char ***pt_arg)
{
	if (*pt_arg[i][j] == '"')
	{
		while (*pt_arg[i][j] != '"')
		{
			if (*pt_arg[i][j] == ''')
}

void	clean_quote(char ***pt_arg)

{
	int	i;

	i = 0;
	while (*pt_arg[i])
	{
		j = 0;
		while (*pt_arg[i][j])
		{
			if (to_del_quote(i, j, pt_arg))
				del_quote(i, j, pt_arg);
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int i;
	char **arg;

	i = 0;
	while (av[i])
		i++;
	arg = malloc(sizeof(char*) * i);
	clean_quote(&arg);
	return(0);
}
