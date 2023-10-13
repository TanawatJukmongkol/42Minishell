/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_program_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/14 04:16:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_clear_process(t_exec *exe)
{
	tun_close_pipe(&exe->_pipes);
	tun_close_files(exe->infile, exe->in_len);
	tun_close_files(exe->outfile, exe->out_len);
	ft_free_split(exe->argv);
	ft_free_split(exe->delimeter);
}

// use after init all kind of box

void	tun_flush_subset(t_token_stream *subset)
{
	t_token	*tmp;

	while (subset->begin != NULL)
	{
		tmp = subset->begin->next;
		if (subset->begin->type == __redirr_append \
			|| subset->begin->type == __redirr_trunc \
			|| subset->begin->type == __redirr_in)
			free(subset->begin->value);
		free(subset->begin);
		subset->begin = tmp;
	}
	subset->begin = NULL;
	subset->last = NULL;
}

void	tun_parent_exit(int status, t_exec *exe, t_token_stream *box, size_t n)
{
	// tun_clear_process(exe);
	tun_close_pipe(&exe->_pipes);
	tun_close_files(exe->infile, exe->in_len);
	tun_close_files(exe->outfile, exe->out_len);
	tun_free_token_box(box, n);
	free(exe->argv);
	free(exe->delimeter);
	ft_clear_envp(exe->_info->_envp.env);
	exit(status);
}

/*
void	tun_free_unused_token(t_token_stream **box)
{
	t_token	*tmp;

	while ((*box)->begin != NULL)
	{
		tmp = (*box)->begin->next;
		if ((*box)->begin->type == __redirr_append \
			|| (*box)->begin->type == __redirr_trunc \
			|| (*box)->begin->type == __redirr_in)
			free((*box)->begin->value);
		free((*box)->begin);
		(*box)->begin = tmp;
	}
	free(*box);
	*box = NULL;
}
*/