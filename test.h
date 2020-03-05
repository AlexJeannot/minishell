#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "get_next_line/get_next_line.h"

char **global_env;

char	**ft_split(char const *s, char c);
void    ft_env(char **t_env);
int ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int car_in_str(char *str, char c);
int special_car_in_str(char *str);
int elem_in_tab(char **tab_input, char* str, char sep);
