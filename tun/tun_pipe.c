/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 20:10:02 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_failsafe_pipe(t_pipe *pipes, size_t err_i)
{
	size_t	i;

	i = 0;
	perror(ERR_MSG);
	while (i < err_i && pipes->box[i] != NULL)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		free(pipes->box[i]);
		i++;
	}
	free(pipes->box);
	pipes->box = NULL;
	return (-1);
}

void	tun_close_pipe(t_pipe *pipes)
{
	size_t	i;

	i = 0;
	if (pipes->box == NULL)
		return ;
	while (i < pipes->n)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		free(pipes->box[i]);
		i++;
	}
	free(pipes->box);
	pipes->box = NULL;
	pipes->n = 0;
}

int	tun_alloc_pipe(t_pipe *pipes, size_t n)
{
	size_t	i;
	int		err;

	i = 0;
	pipes->n = n;
	pipes->box = NULL;
	if (n == 0)
		return (1);
	pipes->box = malloc(sizeof(int *) * n);
	if (pipes->box == NULL)
		return (perror(ERR_MSG), -1);
	while (i < n)
	{
		pipes->box[i] = malloc(sizeof(int) * 2);
		if (pipes->box[i] != NULL)
			err = tun_pipe(pipes->box[i]);
		if (pipes->box[i] == NULL || err == -1)
			return (sb_failsafe_pipe(pipes, i));
		i++;
	}
	return (1);
}
