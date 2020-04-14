#include "../includes/parsing.h"

int	parsing(char *line)
{
	char **stock;

	check(line);
	stock = split_plus(line, ';');
	list_it(stock);
	return (1);
}
