/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_process_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 13:19:37 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_clear_process(t_exec *exe)
{
	tun_close_files(exe->infile, exe->in_len);
	tun_close_files(exe->outfile, exe->out_len);
	if (exe->argv)
		ft_free_split(exe->argv);
	if (exe->delimeter)
		free(exe->delimeter);
}

static void	sb_exit(int isexe)
{
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES)
	{
		if (isexe != 0)
			exit(126);
		exit(1);
	}
	if (errno != 0)
		exit(1);
	exit(0);
}

void	tun_process_exit(int status, t_exec *exe, t_token_stream *box, size_t n)
{
	tun_close_pipe(&exe->_pipes);
	tun_clear_process(exe);
	tun_free_token_box(box, n);
	sb_exit(status);
}
