/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/09 03:05:50 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static void	sb_failsafe_pipe(t_main *info, t_pipe *pipes, size_t err_i)
{
	size_t	i;

	i = 0;
	(void)info;
	while (i < err_i && pipes->box[i] != NULL)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		free(pipes->box[i]);
		i++;
	}
	free(pipes->box);
}

void	tun_close_pipe(t_main *info, t_pipe *pipes)
{
	size_t	i;

	i = 0;
	(void)info;
	while (i < pipes->n)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		free(pipes->box[i]);
		i++;
	}
	// heap_free(&info->_mem, pipes->box);
	free(pipes->box);
}

int	tun_alloc_pipe(t_main *info, t_pipe *pipes, size_t n)
{
	size_t	i;
	int		err;

	i = 0;
	pipes->n = n;
	if (n == 0)
	{
		pipes->box = NULL;
		return (1);
	}
	pipes->box = malloc(sizeof(int *) * n);
	if (pipes->box == NULL)
		return (perror(ERR_MSG), -1);
	while (i < n)
	{
		pipes->box[i] = malloc(sizeof(int) * 2);
		if (pipes->box[i] != NULL)
			err = tun_pipe(pipes->box[i]);
		if (pipes->box[i] == NULL || err == -1)
			return (perror(ERR_MSG), sb_failsafe_pipe(info, pipes, i), -1);
		i++;
	}
	return (1);
}