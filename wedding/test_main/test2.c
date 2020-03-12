#include <libc.h>

char	**split_plus(char *str, char charset);

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int		is_esc(char *str, int i)
{
	if (str[i] == '\\' && (str[i + 1] == '"' || str[i + 1] == '\''))
		return (1);
	i++;
	return (0);
}

static int		spot_esc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_esc(str, i))
			return (1);
		i++;
	}
	return (0);
}

static char		*rm_slash(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	if (!(tmp = malloc(ft_strlen(str))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_esc(str, i))
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static char		**clean_esc_quote(char **stk)
{
	char	*tmp;
	int		i;

	i = 0;
	while (stk[i])
	{
		if (spot_esc(stk[i]))
		{
			tmp = rm_slash(stk[i]);
			free(stk[i]);
			stk[i] = tmp;
		}
		i++;
	}
	return (stk);
}

int main()
{
	char buf[1000];
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
	tab = clean_esc_quote(tab);
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
