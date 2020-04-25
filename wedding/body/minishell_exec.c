#include "../includes/exec.h"

void exec_prompt(void)
{
	char *dir;
	char **split_result_1;
	char **split_result_2;

	split_result_1 = ft_split(global_env[search_in_array(global_env, "PWD", '=')], '=');
	split_result_2 = ft_split(split_result_1[1], '/');
	dir = split_result_2[str_array_length(split_result_2) - 1];
	write(1, "\033[38;5;208m", 12);
	write(1, dir, ft_strlen(dir));
	write(1, " ", 1);
	write(1, "\033[38;5;196m", 12);
	write(1, "}> ", 3);
	write(1, "\033[0m", 4);
	free_str_array(split_result_1);
	free_str_array(split_result_2);
}

int exec_instructions(void)
{
	int status;

	status = 0;
	if (ft_strcmp(lst->cmd, "pwd") == 0 || ft_strcmp(lst->cmd, "echo") == 0 || ft_strcmp(lst->cmd, "env") == 0)
		ft_builtins(lst->cmd, lst->raw);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		ft_cd(lst->arg);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		status = ft_export(lst->arg);
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		status = ft_unset(lst->arg);
	else if (ft_strcmp(lst->cmd, "exit") != 0)
		ft_program(lst->cmd, lst->raw);
	return (status);
}

void exec_child(int is_prev_piped, int exit_status)
{
	if (is_prev_piped == 1)
		exit_status = 0;
	setup_command(exit_status);
	if (lst->rdo_type != 0 || lst->rdc_type != 0)
		manage_redirection();
	exit_status = exec_instructions();
	if (lst->pipe == 0)
		send_env(p_fd);
	//ft_leaks("END OF CHILD\n");
	ft_exit(exit_status);
}

int exec_father(int exit_status)
{
	int ret_child;

	waitpid(child_pid, &ret_child, 0);
	if (WIFEXITED(ret_child))
		exit_status = WEXITSTATUS(ret_child);
	receive_env(p_fd);
	filtered_env = filter_env(global_env, filtered_env);
	return (exit_status);
}

int exec_command_line(char *line, int exit_status)
{
	p_fd[0] = -1;
	p_fd[1] = -1;
	parsing(line);
	setup_pipe_and_process(exit_status);
	exit_status = exec_father(exit_status);
	return (exit_status);
}