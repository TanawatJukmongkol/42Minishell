/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/04 20:15:50 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_init_exec_parent(t_exec *exe, t_main *info)
{
	exe->_info = info;
	if (tun_alloc_pipe(info, &exe->_pipes, exe->_pipes.n) == -1)
		return (0);
	return (1);
}

int	tun_init_exec_child(t_exec *exe, t_token_stream *subset)
{
	int	in;
	int	out;

	exe->argv = tun_get_argv(subset, exe->_info);
	if (exe->argv == NULL)
		return (0);
	in = tun_get_infile(subset, exe);
	out = tun_get_outfile(subset, exe);
	return (in == 1 && out == 1);
}

t_exec	tun_exec_init(void)
{
	t_exec	exe;

	exe._info = NULL;
	exe.argv = NULL;
	exe.delimeter = NULL;
	exe.envp = NULL;
	exe.in_len = 0;
	exe.infile = NULL;
	exe.out_len = 0;
	exe.outfile = NULL;
	return (exe);
}