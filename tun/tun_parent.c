/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/13 14:28:05 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static void	sb_big_wait(t_exec *exe, int *pid, size_t n, int ok)
{
	size_t	i;
	int		e;
	int		stat;

	i = 0;
	if (ok == 0)
		return ;
	while (i < n)
	{
		if (pid[i] != -1 && pid[i] != BUILTIN_PID)
		{
			e = tun_waitpid(pid[i], &stat, WUNTRACED);
			if (e != -1)
				errno = WEXITSTATUS(stat) % 255;
		}
		i++;
	}
	exe->_info->_ngong = errno;
}

static void	sb_dad_buy_milk(t_token_stream *box, t_exec *exe, int *pid, int e)
{
	if (!e)
		return ;
	pid[0] = BUILTIN_PID;
	if (tun_builin_handler(box, pid, exe) == -1)
	{
		pid[0] = tun_fork();
		if (pid[0] != 0)
			return ;
		e = tun_heredoc(exe);
		e = tun_redirct(exe->infile, exe->in_len, STDIN_FILENO, e);
		e = tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO, e);
		if (e)
			tun_execve(exe);
		tun_parent_exit(errno, exe, box);
	}
}

static int	sb_single_mom(t_token_stream *box, t_exec *exe, int *pid)
{
	int	e;

	if (tun_init_box(box[0], exe) == 0)
		tun_parent_exit(ENOMEM, exe, box);
	tun_get_argv(box[0], exe);
	e = tun_get_infile(box[0], exe);
	if (e)
		e = tun_get_outfile(box[0], exe);
	if (errno == ENOMEM)
		tun_parent_exit(ENOMEM, exe, box);
	tun_flush_subset(&box[0]);
	sb_dad_buy_milk(box, exe, pid, e);
	tun_clear_process(exe);
	return (e);
}

static void	sb_family(t_exec *exe, t_token_stream *box, int *pid_box)
{
	size_t	i;

	i = 0;
	while (i <= exe->_pipes.n)
	{
		pid_box[i] = tun_fork();
		if (pid_box[i] == 0)
			tun_child_process(exe, box, pid_box, i);
		else if (pid_box[i] == -1)
			break ;
		i++;
	}
	tun_close_pipe(&exe->_pipes);
}

void	tun_parent_process(t_main *info, t_token_stream *box, size_t pipe_n)
{
	int		*pid_box;
	int		e;
	t_exec	exe;

	e = 1;
	if (tun_init_exec_parent(&exe, info, pipe_n) == 0)
		tun_parent_exit(ENOMEM, &exe, box);
	pid_box = malloc(sizeof(int) * (pipe_n + 1));
	if (pid_box == NULL)
		tun_parent_exit(ENOMEM, &exe, box);
	if (pipe_n == 0)
		e = sb_single_mom(box, &exe, pid_box);
	else
		sb_family(&exe, box, pid_box);
	sb_big_wait(&exe, pid_box, pipe_n + 1, e);
	free(pid_box);
}