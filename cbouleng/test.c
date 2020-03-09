#include <stdio.h>
#include "minishell.h"

char	**ft_split_plus(char *str, char *charset);

void init(t_stt *vs)
{
	printf("%d\n", vs->i);
	vs->i = 55;
}

int main()
{
	t_stt *vs;

	vs = malloc(sizeof(t_stt));
	vs->i = 50;
	init(vs);
	printf("!%d\n", vs->i);

	return (0);
}
