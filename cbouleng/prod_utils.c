#include <stdio.h>

void	printf_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		printf("[%s]\n", tab[i++]);
}
