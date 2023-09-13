/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/12 20:28:34 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// static int	**sb_assign_pipe(t_pipex *info)
// {
// 	int	i;
// 	int	err_i;

// 	i = 0;
// 	while (i < info->cmd_len)
// 	{
// 		if (pipe(info->pbox[i]) == -1)
// 		{
// 			perror(info->shell);
// 			err_i = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (i == info->cmd_len)
// 		return (info->pbox);
// 	i = 0;
// 	while (i < err_i)
// 	{
// 		px_close(info->pbox[i][0], info->shell);
// 		px_close(info->pbox[i][1], info->shell);
// 		i++;
// 	}
// 	return (NULL);
// }

// static int	**sb_allocate_pipe(t_pipex *info)
// {
// 	int	i;

// 	info->pbox = lm_malloc(sizeof(int *), info->cmd_len, &info->head);
// 	if (info->pbox == NULL)
// 		return (perror(info->shell), NULL);
// 	i = 0;
// 	while (i < info->cmd_len)
// 	{
// 		info->pbox[i] = lm_malloc(sizeof(int), 2, &info->head);
// 		if (info->pbox[i] == NULL)
// 			return (perror(info->shell), NULL);
// 		i++;
// 	}
// 	return (sb_assign_pipe(info));
// }

static void	sb_failsafe_pipe(t_main *info, t_pipe *pipes, size_t err_i)
{
	size_t	i;

	i = 0;
	while (i < err_i && pipes->box[i] != NULL)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		heap_free(&info->_mem, pipes->box[i]);
		i++;
	}
	heap_free(&info->_mem, pipes->box);
}

void	tun_close_pipe(t_main *info, t_pipe *pipes)
{
	size_t	i;

	i = 0;
	while (i < pipes->n)
	{
		close(pipes->box[i][0]);
		close(pipes->box[i][1]);
		heap_free(&info->_mem, pipes->box[i]);
		i++;
	}
	heap_free(&info->_mem, pipes->box);
}

int	tun_alloc_pipe(t_main *info, t_pipe *pipes, size_t n)
{
	size_t	i;
	int		err;

	i = 0;
	pipes->box = ft_malloc(sizeof(int *), n, &info->_mem, NULL);
	if (pipes->box == NULL)
		return (perror(ERR_MSG), -1);
	pipes->n = n;
	while (i < n)
	{
		pipes->box[i] = ft_malloc(sizeof(int), 2, &info->_mem, NULL);
		if (pipes->box[i] != NULL)
			err = tun_pipe(pipes->box[i]);
		if (pipes->box[i] == NULL || err == -1)
			return (perror(ERR_MSG), sb_failsafe_pipe(info, pipes, i), -1);
		i++;
	}
	return (1);
}