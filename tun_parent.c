/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/18 02:10:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static void	sb_big_wait(t_exec *exe, pid_t *pid, size_t n, int ok)
{
	size_t	i;
	int		e;
	int		stat;

	i = 0;
	if (ok == 0)
		return ;
	while (i < n)
	{
		if (pid[i] != -1)
		{
			e = tun_waitpid(pid[i], &stat, WUNTRACED);
			if (e != -1)
				exe->_info->_ngong = WEXITSTATUS(stat);
		}
		i++;
	}
}

/*
0 = don't run child
1 = run child
*/

static int	sb_dad_buy_milk(t_token_stream *box, t_exec *exe, pid_t *pid, int e)
{
	if (!e)
		return (0);
	if (tun_builtin_parent(box, pid, exe, 0) == -1)
	{
		pid[0] = tun_fork();
		if (pid[0] != 0)
			return (pid[0] != -1);
		e = tun_dup_heredoc(exe->_heredoc.box[0][0], STDIN_FILENO) != -1;
		e = tun_redirct(exe->infile, exe->in_len, STDIN_FILENO, e);
		e = tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO, e);
		tun_close_pipe(&exe->_heredoc);
		tun_execve(exe, e);
		tun_process_exit(1, exe, box, exe->_pipes.n);
	}
	return (0);
}

static int	sb_single_mom(t_token_stream *box, t_exec *exe, pid_t *pid, int *w)
{
	int	e;

	if (tun_init_box(box[0], exe) == 0)
		tun_process_exit(0, exe, box, exe->_pipes.n);
	e = tun_get_argv(box[0], exe);
	if (e)
		e = tun_get_infile(box[0], exe);
	if (e)
		e = tun_get_outfile(box[0], exe);
	if (errno == ENOMEM)
		tun_process_exit(0, exe, box, exe->_pipes.n);
	*w = sb_dad_buy_milk(box, exe, pid, e);
	tun_close_pipe(&exe->_heredoc);
	tun_clear_process(exe);
	return (e);
}

static void	sb_family(t_exec *exe, t_token_stream *box, pid_t *pid_box)
{
	size_t	i;

	i = 0;
	while (i <= exe->_pipes.n)
	{
		pid_box[i] = tun_fork();
		if (pid_box[i] == 0)
			return (tun_child_process(exe, box, pid_box, i));
		else if (pid_box[i] == -1)
			break ;
		i++;
	}
	tun_close_pipe(&exe->_pipes);
	tun_close_pipe(&exe->_heredoc);
}

void	tun_parent_process(t_main *info, t_token_stream *box, size_t pipe_n)
{
	pid_t	*pid_box;
	int		e;
	t_exec	exe;
	int		wait;

	e = 1;
	wait = 1;
	if (tun_init_exec_parent(&exe, info, pipe_n) == 0)
		tun_process_exit(0, &exe, box, pipe_n);
	pid_box = malloc(sizeof(int) * (pipe_n + 1));
	if (pid_box == NULL)
		tun_process_exit(0, &exe, box, pipe_n);
	if (tun_heredoc(box, pipe_n, &exe) == 0)
		tun_process_exit(0, &exe, box, pipe_n);
	if (pipe_n == 0)
		e = sb_single_mom(box, &exe, pid_box, &wait);
	else
		sb_family(&exe, box, pid_box);
	sb_big_wait(&exe, pid_box, pipe_n + 1, e == 1 && wait == 1);
	free(pid_box);
}
