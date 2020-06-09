#include "../includes/exec.h"

void exec_prompt(void)
{
	char *dir;
	char **split_result;

	split_result = ft_split(pwd_path, '/');
	dir = split_result[str_array_length(split_result) - 1];
	write(1, "\033[38;5;208m", 12);
	write(1, dir, ft_strlen(dir));
	write(1, " ", 1);
	write(1, "\033[38;5;196m", 12);
	write(1, "}> ", 3);
	write(1, "\033[0m", 4);
	free_str_array(split_result);
}

int exec_instructions(void)
{
	int status;

	status = 0;
	if (lst->cmd)
	{
		if (ft_strcmp(lst->cmd, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(lst->cmd, "echo") == 0)
			ft_echo(lst->arg);
		else if (ft_strcmp(lst->cmd, "env") == 0)
			ft_env(lst->arg);
		else if (ft_strcmp(lst->cmd, "cd") == 0)
			ft_cd(lst->arg);
		else if (ft_strcmp(lst->cmd, "export") == 0)
			status = ft_export(lst->arg);
		else if (ft_strcmp(lst->cmd, "unset") == 0)
			status = ft_unset(lst->arg);
		else if (ft_strcmp(lst->cmd, "exit") != 0)
			ft_program(lst->cmd, lst->raw);
	}
	return (status);
}

void exec_child(int is_prev_piped, int exit_status, int write_pend, int write_pwdend)
{
	if (is_prev_piped == 1)
		exit_status = 0;
	setup_command(exit_status);
	if (lst->rdo_type != 0 || lst->rdc_type != 0)
		manage_redirection();
	exit_status = exec_instructions();
	if (lst->pipe == 0)
		send_env(write_pend, write_pwdend);
	else
	{
		close(write_pend);
		close(write_pwdend);
	}
	ft_exit(exit_status);
}

int exec_father(int exit_status, int read_pend, int read_pwdend)
{
	int ret_child;

	waitpid(child_pid, &ret_child, 0);
	if (WIFEXITED(ret_child))
		exit_status = WEXITSTATUS(ret_child);
	receive_env(read_pend, read_pwdend);
	filtered_env = filter_env(global_env, filtered_env);
	close(read_pend);
	return (exit_status);
}

int exec_command_line(char *line, int exit_status)
{
	int *read_fd;

	if (!(read_fd = (int *)malloc(sizeof(int) * 2)))
        ft_error('\0', "Malloc", NULL);
	parsing(line);
	read_fd = setup_pipe_and_process(exit_status, read_fd);
	exit_status = exec_father(exit_status, read_fd[0], read_fd[1]);
	free(read_fd);
	return (exit_status);
}