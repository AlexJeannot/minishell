#include "./includes/exec.h"

void display_prompt(void)
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

void exec_child(int exit_status, int process_fd[2], int redirection_fd[2])
{
	replace_exit_status(exit_status);
	if (lst->rdo_type != 0 || lst->rdc_type != 0)
		set_rdo();
	if (lst->rdc_type != 0)
		dup2(redirection_fd[1], STDOUT_FILENO);
	else if (lst->pipe == 1)
		dup2(process_fd[1], STDOUT_FILENO);
	exit_status = exec_instructions();
	if (lst->pipe == 0)
		send_env(process_fd);
	ft_exit(exit_status);
}

int exec_father(int exit_status, int process_fd[2], int redirection_fd[2])
{
	int ret_child;

	waitpid(child_pid, &ret_child, 0);
	if (WIFEXITED(ret_child))
		exit_status = WEXITSTATUS(ret_child);
	if (lst->rdc_type != 0)
		receive_redirection(redirection_fd);
	if (lst->pipe == 1)
		exit_status = receive_pipe(process_fd);
	else if (env_need_update(lst->cmd))
		receive_env(process_fd);
	if (ft_strcmp(lst->cmd, "exit") == 0)
		ft_exit(0);
	filtered_env = filter_env(global_env, filtered_env);
	return (exit_status);
}

int exec_command_line(int exit_status, int process_fd[2], int redirection_fd[2], char *line)
{
	t_list *tmp;

	parsing(line);
	tmp = lst;
	while (lst)
	{
		setup_command();
		if (lst->cmd)
		{
			child_pid = fork();
			if (child_pid == 0)
				exec_child(exit_status, process_fd, redirection_fd);
			else
				exit_status = exec_father(exit_status, process_fd, redirection_fd);
		}
		lst = lst->next;
	}
	lst = tmp;
	return (exit_status);
}