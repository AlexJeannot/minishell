#include "../includes/parsing.h"

char* map;

int	parsing(char *line)
{
	char **stock;

	map = map_quote(line, 0);
	check(line);
	stock = split_plus(line, ';');
	list_it(stock);
	return (1);
}
