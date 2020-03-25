#include "minishell.h"

static void	to_del_quote(int i)
{
	int		j;
	int		len;
	char*	tmp;

	len = ft_strlen(lst->arg[i]);
	if (!(tmp = malloc(len - 1)))
		exit(1);
	j = 0;
	while (j < len - 2)
	{
		tmp[j] = lst->arg[i][j + 1];
		j++;
	}
	tmp[j] = '\0';
	lst->arg[i] = tmp;
}

void		clean_quote(void)
{
	int	i;

	i = 0;
	while (lst->arg[i])
	{
		if (lst->arg[i][0] == '\'' || lst->arg[i][0] == '"')
			to_del_quote(i);
		i++;
	}
	//clean_esc_quote(stock);
}
