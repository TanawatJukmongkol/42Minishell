/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_program_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/10 23:51:01 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_clear_process(t_exec *exe)
{
	tun_close_pipe(&exe->_pipes);
	tun_close_files(exe->infile, exe->in_len);
	tun_close_files(exe->outfile, exe->out_len);
	ft_clear_envp(exe->argv);
	ft_clear_envp(exe->delimeter);
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

void	tun_parent_exit(int status, t_exec *exe, t_token_stream *box)
{
	tun_clear_process(exe);
	tun_free_token_box(box, exe->_pipes.n);
	ft_clear_envp(exe->_info->_envp.env);
	exit(status);
}