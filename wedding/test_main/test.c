#include <libc.h>

char	**split_plus(char *str, char charset);

int main()
{
	char buf[1000];
	char *str;
	char **tab;
	int fd;
	int rdb;
	int i;

	if (!(fd = open("txt", O_RDONLY)))
	{
		printf("@\n");
		return (0);
	}
	if (!(rdb = read(fd, buf, 1000)))
	{
		printf("#\n");
		return (0);
	}
	buf[rdb] = '\0';
	tab = split_plus(buf, '|');
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
