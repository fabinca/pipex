/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:16:25 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/01 13:20:45 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	parent_process(t_data *dt, pid_t pid)
{
	close(dt->oldpipe[0]);
	close(dt->oldpipe[1]);
	waitpid(pid, NULL, 0);
	dup2(dt->newpipe[0], dt->oldpipe[0]);
	close(dt->newpipe[0]);
	dup2(dt->newpipe[1], dt->oldpipe[1]);
	close(dt->newpipe[1]);
}

static void	child_process(t_data *dt, char **envp, int ct)
{
	if (ct == 0)
	{
		if (dup2(dt->fd_in, dt->oldpipe[0]) < 0)
			perror("dup2 reading from fd_in");
		close(dt->fd_in);
	}
	if (dup2(dt->oldpipe[0], STDIN_FILENO) < 0)
		perror("dup2 replacing stdin");
	close(dt->oldpipe[0]);
	if (ct == dt->cmd_num - 1)
	{
		if (dup2(dt->fd_out, dt->newpipe[1]) < 0)
			perror("dup2 printing to fd_out");
		close(dt->fd_out);
	}
	if (dup2(dt->newpipe[1], STDOUT_FILENO) < 0)
		perror("dup2 replacing stdout");
	close(dt->newpipe[1]);
	close(dt->newpipe[0]);
	close(dt->oldpipe[1]);
	dt->c_p = find_c_path(dt->paths, ft_strjoin("/", dt->cmds[ct][0]), dt->c_p);
	if (dt->c_p)
		execve(dt->c_p, dt->cmds[ct], envp);
	free_t_data(dt);
	exit(EXIT_FAILURE);
}

static int	pipex(t_data *dt, char **envp, int count)
{
	pid_t	pid;

	if (count == dt->cmd_num)
	{
		close(dt->oldpipe[0]);
		close(dt->oldpipe[1]);
		return (0);
	}
	if (pipe(dt->newpipe) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("Fork");
	else if (pid == 0)
		child_process(dt, envp, count);
	else
	{
		parent_process(dt, pid);
		pipex(dt, envp, count + 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		*dt;

	dt = init_tdata(argc, argv, envp);
	if (dt->error == 0)
	{
		if (pipe(dt->oldpipe) < 0)
			perror("Pipe");
		pipex(dt, envp, 0);
	}
	free_t_data(dt);
	return (0);
}
