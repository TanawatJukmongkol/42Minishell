/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_process_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/18 22:17:17 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_clear_process(t_exec *exe)
{
	tun_close_files(exe->infile, exe->in_len);
	tun_close_files(exe->outfile, exe->out_len);
	if (exe->argv)
		ft_free_split(exe->argv);
}

static void	sb_exit(int isexe, int in_err)
{
	if (in_err)
		exit(0);
	if (errno == ENOENT)
		exit(127);
	if (errno == EACCES || errno == EPERM)
	{
		if (isexe != 0)
			exit(126);
		exit(1);
	}
	exit(errno != 0);
}

static int	sb_infile_err(t_exec *exe)
{
	int	i;

	i = 0;
	if (exe->argv[0] != NULL)
		return (0);
	while (i < exe->in_len)
	{
		if (exe->infile[i] == -1)
			return (1);
		i++;
	}
	return (0);
}

void	tun_process_exit(int status, t_exec *exe, t_token_stream *box, size_t n)
{
	int	in_err;

	in_err = 0;
	if (sb_infile_err(exe))
		in_err = 1;
	tun_close_pipe(&exe->_pipes);
	tun_close_pipe(&exe->_heredoc);
	tun_clear_process(exe);
	tun_free_token_box(box, n);
	sb_exit(status, in_err);
}
