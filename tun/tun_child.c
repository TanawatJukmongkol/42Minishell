/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/13 13:41:29 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

/*
1.) close all pipe
2.) close all infile
3.) close all outfile
4.) deallocate all heap
5.) exit child process
*/

static int	sb_redirect_pipe(t_exec *exe, size_t i, int e)
{
	e = 1;
	if (i != 0)
		e = tun_dup2(exe->_pipes.box[i - 1][0], STDIN_FILENO) != -1;
	if (i != exe->_pipes.n)
		e = tun_dup2(exe->_pipes.box[i][1], STDOUT_FILENO) != -1;
	return (e);
}

void	hee(int sig)
{
	exit(sig);
}

void	tun_child_process(t_exec *exe, t_token_stream *box, int *pid, size_t i)
{
	int	e;

	if (tun_init_box(box[i], exe) == 0)
		tun_parent_exit(ENOMEM, exe, box);
	tun_get_argv(box[i], exe);
	e = tun_get_infile(box[i], exe);
	if (e)
		e = tun_get_outfile(box[i], exe);
	tun_flush_subset(&box[i]);
	if (tun_builin_handler(box, pid, exe) == -1)
	{
		free(pid);
		e = tun_heredoc(exe);
		e = sb_redirect_pipe(exe, i, e);
		e = tun_redirct(exe->infile, exe->in_len, STDIN_FILENO, e);
		e = tun_redirct(exe->outfile, exe->out_len, STDIN_FILENO, e);
		tun_close_pipe(&exe->_pipes);
		if (e)
			tun_execve(exe);
		tun_parent_exit(errno, exe, box);
	}
	tun_clear_process(exe);
}