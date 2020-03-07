#include <stdio.h>
#include "minishell.h"

char	**ft_split_plus(char *str, char *charset);

static int	is_pipe(char *stock)
{
	int i;

	i = 0;
	while (stock[i])
	{
		if (stock[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

static t_list	new_trio(t_trio trio)
{
	t_list	*lst;

	lst = NULL;
	if (!(lst = malloc(sizeof(t_list))))
		return (*lst);
	lst->cmd = trio.cmd;
	lst->arg = trio.arg;
	lst->pipe = trio.pipe;
	lst->next = NULL;
	return (*lst);
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

int main()
{
	char **tab;
	int i;
	int j;
	t_list *lst;
	t_list elem;
	t_list *lst_iter;

	if (!(lst = malloc(sizeof(t_list))))
		return (0);
	lst = NULL;
	i = 0;
	tab = ft_split_plus("echo test    cat -e ; bonjour $path oui oui; ert | ert|ert", ";");
	while (tab[i])
	{

	}
	return (0);
}
