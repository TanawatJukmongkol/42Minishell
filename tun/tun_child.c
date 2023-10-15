/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 00:43:13 by tponutha         ###   ########.fr       */
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

void	tun_child_process(t_exec *exe, t_token_stream *box, int *pid, size_t i)
{
	int		e;
	size_t	n;

	n = exe->_pipes.n;
	if (tun_init_box(box[i], exe) == 0)
		tun_parent_exit(ENOMEM, exe, box, n);
	e = tun_get_argv(box[i], exe);
	if (e)
		e = tun_get_infile(box[i], exe);
	if (e)
		e = tun_get_outfile(box[i], exe);
	e = tun_heredoc(exe);
	e = sb_redirect_pipe(exe, i, e);
	e = tun_redirct(exe->infile, exe->in_len, STDIN_FILENO, e);
	e = tun_redirct(exe->outfile, exe->out_len, STDIN_FILENO, e);
	tun_close_pipe(&exe->_pipes);
	if (tun_builin_parent(box, pid, exe, n) == -1)
		tun_execve(exe, e);
	free(pid);
	tun_parent_exit(errno, exe, box, n);
}
