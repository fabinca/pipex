/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:26:48 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/01 13:21:43 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdint.h>

typedef struct s_data
{
	int		cmd_num;
	int		fd_in;
	int		fd_out;
	int		buf;
	int		newpipe[2];
	int		oldpipe[2];
	char	***cmds;
	char	**paths;
	char	*c_p;
	int		error;
}			t_data;

char	*find_c_path(char **paths, char *cmd, char *cmd_path);
t_data	*init_tdata(int argc, char **argv, char **envp);
void	double_free(char **argv, int size);
void	free_t_data(t_data *dt);

#endif
