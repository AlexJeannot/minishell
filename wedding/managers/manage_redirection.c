#include "../includes/minishell.h"

void from_file(void)
{
    int fd;

    if ((fd = open(PATH, O_RDONLY)) == -1)
        printf("ERROR\n");

    while ((ret = read(fd[0], buf, 100)) > 0)
	{
		buf[ret] = '\0';
		piped_str = ft_join(piped_str, buf, ft_len(piped_str), ft_len(buf));
        if (ret < 100)
                break ;
	}
}

void write_file(void)
{
    int fd;
    char *line;
    char *final_str;

    if ((fd = open(PATH, O_CREAT | O_WRONLY)) == -1)
        printf("ERROR\n");
    if (piped_str)
        write(fd, piped_str, ft_strlen(piped_str));
    else
    {
        while (get_next_line(0, &line) > 0)
        {
            final_str = ft_join(final_str, line, ft_len(final_str), ft_len(line));
            free(line);
        }
        free(line);
        write(fd, final_str, ft_strlen(final_str));
        free_str(final_str);
    }
}

void append_file(void)
{
    int fd;
    char *line;
    char *final_str;

    if ((fd = open(PATH, O_CREAT | O_WRONLY | O_APPEND)) == -1)
        printf("ERROR\n");
    if (piped_str)
        write(fd, piped_str, ft_strlen(piped_str));
    else
    {
        while (get_next_line(0, &line) > 0)
        {
            final_str = ft_join(final_str, line, ft_len(final_str), ft_len(line));
            free(line);
        }
        free(line);
        write(fd, final_str, ft_strlen(final_str));
        free_str(final_str);
    }
}
