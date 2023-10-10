/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/10 23:22:52 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// void	sb_single_mom(t_token_stream *subset, t_exec *exe, int *pid_box)
// {
// 	int	e;

// 	e = tun_init_exec_child(exe, subset);
// 	if (e == 1)
// 	{
// 		e &= tun_redirct(exe->infile, exe->in_len, STDIN_FILENO);
// 		e &= tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO);
// 	}
// 	tun_clean_child(exe);
// 	if (e)
// 	{
// 		if (tun_builin_handler(exe->argv[0], exe->argv, exe) == -1)
// 		{
// 			pid_box[0] = tun_fork(ERR_MSG);
// 			if (pid_box[0] == 0)
// 			{
// 				tun_execve(exe);
// 			}	
// 		}
// 	}
// }

// static void	sb_big_wait(int *pid, int n)
// {
// 	int	i;
// 	int	stat;
// 	int	e;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (pid[i] != -1)
// 		{
// 			e = tun_waitpid(pid[i], &stat, WUNTRACED, ERR_MSG);
// 			if (e != -1)
// 				errno = WEXITSTATUS(stat) % 255;
// 		}
// 		i++;
// 	}
// }

// void	tun_parent_process(t_main *info)
// {
// 	size_t			i;
// 	int				*pid_box;
// 	t_token_stream	*token_box;
// 	t_exec			exe;

// 	i = 0;
// 	exe = tun_exec_init();
// 	token_box = tun_split_token(info, &exe._pipes.n);
// 	if (token_box == NULL)
// 		return (perror(ERR_MSG), ft_exit(info, ENOMEM));
// 	if (tun_init_exec_parent(&exe, info) == 0)
// 		return (perror(ERR_MSG), ft_exit(info, ENOMEM));
// 	pid_box = malloc(sizeof(int) * (exe._pipes.n + 1));
// 	if (pid_box == NULL)
// 		return (perror(ERR_MSG), ft_exit(info, ENOMEM));
// 	if (exe._pipes.n == 0)
// 		sb_single_mom(&token_box[0], &exe, pid_box);
// 	else
// 	{
// 		while (i < exe._pipes.n + 1)
// 		{
// 			pid_box[i] = tun_fork(ERR_MSG);
// 			if (pid_box[i] == 0)
// 				return (tun_child_process(&token_box[i], &exe, i));
// 			i++;
// 		}
// 		tun_close_pipe(info, &exe._pipes);
// 	}
// 	sb_big_wait(pid_box, exe._pipes.n);
// 	// TODO : write token box here
// 	tun_free_token_box(token_box, exe._pipes.n);
// 	free(pid_box);
// 	// heap_free(&info->_mem, token_box);
// 	// heap_free(&info->_mem, pid_box);
// }

static void	sb_big_wait(t_exec *exe, int *pid, size_t n)
{
	size_t	i;
	int		e;
	int		stat;

	i = 0;
	while (i < n)
	{
		if (pid[i] != -1)
		{
			e = tun_waitpid(pid[i], &stat, WUNTRACED, ERR_MSG);
			if (e != -1)
				errno = WEXITSTATUS(stat) % 255;
		}
		i++;
	}
	exe->_info->_ngong = errno;
}

static void	sb_single_mom(t_token_stream *box, t_exec *exe, int *pid)
{
	int	e;

	if (tun_init_box(box[0], exe) == 0)
		tun_parent_exit(ENOMEM, exe, box);
	tun_get_argv(box[0], exe);
	e = tun_get_infile(box[0], exe);
	if (e)
		e = tun_get_outfile(box[0], exe);
	tun_flush_subset(&box[0]);
	if (e)
	{
		if (tun_builin_handler(exe->argv[0], exe->argv, exe) == -1)
		{
			pid[0] = tun_fork(ERR_MSG);
			if (pid[0] == 0)
			{
				tun_execve(exe);
				tun_parent_exit(errno, exe, box);
			}
		}
	}
	tun_clear_process(exe, box);
}

void	tun_parent_process(t_main *info, t_token_stream *box, size_t pipe_n)
{
	size_t	i;
	int		*pid_box;
	t_exec	exe;

	i = 0;
	if (tun_init_exec_parent(&exe, info, pipe_n) == 0)
		tun_parent_exit(ENOMEM, &exe, box);
	pid_box = malloc(sizeof(int) * (pipe_n + 1));
	if (pid_box == NULL)
		tun_parent_exit(ENOMEM, &exe, box);
	if (pipe_n == 0)
		sb_single_mom(box, &exe, pid_box);
	else
	{
		while (i <= pipe_n)
		{
			pid_box[i] = tun_fork(ERR_MSG);
			if (pid_box[i] == 0)
				return ;
			else if (pid_box[i] == -1)
				break ;
			i++;
		}
	}
	sb_big_wait(&exe, pid_box, pipe_n + 1);
	free(pid_box);
	tun_clear_process(&exe, box);
}