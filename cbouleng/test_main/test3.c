#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;
	int		i;
	int		len;

	i = 0;
	len = 0;
	str = "PATH";
	while (str[i++])
	{
		len++;
	}
	printf("%d\n", len);
	printf("%d\n", i);
	return (0);
}
