#include <stdio.h>

char	**ft_split_plus_2(char *str, char charset);

int main()
{
	char **str;
	int i;

	str = ft_split_plus_2("echo \"line\" ; cat 'donc ; oui' ", ';');
	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return (0);
}
