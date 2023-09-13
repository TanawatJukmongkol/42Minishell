/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 23:28:26 by tponutha         ###   ########.fr       */
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

void	tun_clean_child(t_exec *exe)
{
	int	i;

	i = 0;
	tun_close_pipe(exe->_info, exe->_pipes);
	while (i < exe->in_len)
	{
		tun_close(exe->infile[i]);
		i++;
	}
	i = 0;
	while (i < exe->out_len)
	{
		tun_close(exe->outfile[i]);
		i++;
	}
	if (exe->infile != NULL)
		heap_free(&exe->_info->_mem, exe->infile);
	if (exe->outfile != NULL)
		heap_free(&exe->_info->_mem, exe->outfile);
}

int		tun_redirct(int *fdes, int len, int std)
{
	if (fdes == NULL)
		return (len != -1);
	while (len > 0 && fdes[len] != std)
	{
		if (tun_dup2(len, len - 1) == -1)
			return (0);
		len--;
	}
	return (tun_dup2(0, std) != -1);
}

// child process function

void	tun_child_process(t_token_stream *subset, t_exec *exe, int child_no)
{
	int	e;

	e = tun_init_exec_child(exe, subset);
	if (e == 1)
	{
		if (child_no != 0)
			e &= tun_dup2(exe->_pipes->box[child_no][0], STDIN_FILENO) != -1;
		if (child_no != exe->_pipes->n - 1)
			e &= tun_dup2(exe->_pipes->box[child_no][1], STDOUT_FILENO) != -1;
		e &= tun_redirct(exe->infile, exe->in_len, STDIN_FILENO);
		e &= tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO);
	}
	tun_clean_child(exe);
	if (e)
	{
		if (tun_builin_handler(exe->argv[0], exe->argv, exe->_info) == -1)
			execve(exe->argv[0], exe->argv, exe->_info->_envp.env);
	}
	heap_purge(&exe->_info->_mem);
	tun_child_exit(&exe->_info->_mem, errno);
}
