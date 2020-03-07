
#include "minishell.h"

static int	ft_exit(int status)
{
	exit(status);
}

static int	is_pipe(char *stock)
{
	while (stock[i])
	{
		if (stock[i] == "|")
			return (1);
		i++;
	}
	return (0);
}

static void	prompt(t_stt *vs)
{
	if ()
		write(1, "$ ", 2);
}

static t_trio get_trio(char *stock, int pipe)
{
	int		i;
	int		j;
	char	**content;
	t_trio	trio;

	content = ft_split_plus(stock, " ");
	trio.cmd = content[0];
	i = 1;
	while (content[i])
		i++;
	if (!(trio.arg = malloc(sizeof(char*) * i + 1)))
		return (trio);
	i = 1;
	j = 0;
	while (content[i])
		trio.arg[j++] = content[i++];
	trio.arg[j] = NULL;
	trio.pipe = pipe; 
	return (trio);
}

static void	parsing(char *line, t_stt *vs)
{
	vs->stock = ft_split_plus(line, ";");		
	list_it(vs);
}

int		main(int ac, char **av, char **env)
{
	t_stt	vs;
	char 	*line;

	vs = init(ac, av, env);
	prompt(vs);
	while (!get_next_line(0, &line))
	{
		get_env(env, vs);
		parsing(line, vs);
		free(line);
		prompt(vs);
	}
	free(line);
	return (0);
