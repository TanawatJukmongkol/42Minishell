/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 23:13:56 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_init_exec_parent(t_exec *exe, t_main *info, size_t pipe_n)
{
	int	err;

	exe->_info = info;
	err = tun_alloc_pipe(&exe->_pipes, pipe_n);
	if (err != -1)
		err = tun_alloc_pipe(&exe->_heredoc, pipe_n + 1);
	exe->argv = NULL;
	exe->in_len = 0;
	exe->infile = NULL;
	exe->out_len = 0;
	exe->outfile = NULL;
	if (err == -1)
		tun_close_pipe(&exe->_pipes);
	return (err == 1);
}

static int	sb_count_token(t_token_stream subset, t_exec *exe)
{
	int	argv_len;

	argv_len = 0;
	exe->in_len = 1;
	exe->out_len = 1;
	while (subset.begin != NULL)
	{
		if (subset.begin->type == __redirr_in \
			|| subset.begin->type == __here_doc)
			exe->in_len++;
		else if (subset.begin->type == __redirr_trunc \
				|| subset.begin->type == __redirr_append)
			exe->out_len++;
		else if (subset.begin->type == __argv \
				|| subset.begin->type == __cmd)
			argv_len++;
		subset.begin = subset.begin->next;
	}
	return (argv_len);
}

int	tun_init_box(t_token_stream subset, t_exec *exe)
{
	int	argv_len;

	argv_len = sb_count_token(subset, exe);
	exe->argv = malloc(sizeof(char *) * (argv_len + 1));
	exe->infile = malloc(sizeof(int) * exe->in_len);
	exe->outfile = malloc(sizeof(int) * exe->out_len);
	if (exe->argv == NULL || exe->infile == NULL || exe->outfile == NULL)
	{
		free(exe->argv);
		free(exe->infile);
		free(exe->outfile);
		return (0);
	}
	return (1);
}
