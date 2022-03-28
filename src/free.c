/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:09 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/01 13:21:14 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	double_free(char **argv, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!argv[i])
			break ;
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_t_data(t_data *dt)
{
	int	i;

	double_free(dt->paths, 1000);
	i = 0;
	while (i < dt->cmd_num)
	{
		double_free(dt->cmds[i], 7);
		i++;
	}
	free(dt->cmds);
	free(dt->c_p);
	free(dt);
}
