/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:31:16 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/01 13:21:35 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_c_path(char **paths, char *cmd, char *cmd_path)
{
	free(cmd_path);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd);
			return (cmd_path);
		}
		else
			free(cmd_path);
		paths++;
	}
	ft_putstr_fd(++cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(--cmd);
	return (NULL);
}

static char	**init_paths(char **envp)
{
	char	**paths;

	while (envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_split((*(envp) + 5), ':');
			break ;
		}
		envp++;
	}
	return (paths);
}

static char	***init_commands(const int arg_num, char **argv)
{
	char	***cmds;
	int		i;

	i = 0;
	cmds = (char ***)ft_calloc(sizeof(char ***), arg_num + 1);
	while (i < arg_num)
	{
		cmds[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	return (cmds);
}

t_data	*init_tdata(int argc, char **argv, char **envp)
{
	t_data		*dt;

	dt = (t_data *)ft_calloc(sizeof(t_data), 1);
	dt->error = 0;
	dt->cmd_num = argc - 3;
	dt->fd_in = open(argv[1], O_RDONLY);
	if (dt->fd_in < 0)
	{
		perror(argv[1]);
		dt->error = 1;
	}
	dt->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (dt->fd_out < 0)
	{
		perror(argv[argc - 1]);
		dt->error = 1;
	}
	dt->cmds = init_commands(dt->cmd_num, argv);
	dt->paths = init_paths(envp);
	dt->c_p = NULL;
	return (dt);
}
