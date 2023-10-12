/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/13 02:48:24 by tponutha         ###   ########.fr       */
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

// void	tun_clean_child(t_exec *exe)
// {
// 	int	i;

// 	i = 0;
// 	if (exe->_pipes.n > 0)
// 		tun_close_pipe(exe->_info, &exe->_pipes);
// 	while (i < exe->in_len)
// 	{
// 		tun_close(exe->infile[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < exe->out_len)
// 	{
// 		tun_close(exe->outfile[i]);
// 		i++;
// 	}
// 	if (exe->infile != NULL)
// 		free(exe->infile);
// 	if (exe->outfile != NULL)
// 		free(exe->outfile);
// }

// int		tun_redirct(int *fdes, int len, int std)
// {
// 	if (fdes == NULL)
// 		return (len != -1);
// 	while (len > 0 && fdes[len] != std)
// 	{
// 		if (tun_dup2(fdes[len], fdes[len - 1]) == -1)
// 			return (0);
// 		len--;
// 	}
// 	return (tun_dup2(0, std) != -1);
// }

// // child process function

// void	tun_child_process(t_token_stream *subset, t_exec *exe, size_t child_no)
// {
// 	int	e;

// 	e = tun_init_exec_child(exe, subset);
// 	if (e == 1)
// 	{
// 		if (child_no != 0)
// 			e &= tun_dup2(exe->_pipes.box[child_no - 1][0], STDIN_FILENO) != -1;
// 		if (child_no != exe->_pipes.n)
// 			e &= tun_dup2(exe->_pipes.box[child_no][1], STDOUT_FILENO) != -1;
// 		e &= tun_redirct(exe->infile, exe->in_len, STDIN_FILENO);
// 		e &= tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO);
// 	}
// 	tun_clean_child(exe);
// 	if (e)
// 	{
// 		if (tun_builin_handler(exe->argv[0], exe->argv, exe) == -1)
// 			tun_execve(exe);
// 	}
// 	ft_clear_envp(exe->envp);
// 	ft_tokenfree(&exe->_info->_token);
// 	// heap_purge(&exe->_info->_mem);
// 	tun_parent_exit(exe, errno);
// }


void	tun_child_process(t_exec *exe, t_token_stream *box, int *pid, int i)
{
	int	e;

	if (tun_init_box(box[i], exe) == 0)
		tun_parent_exit(ENOMEM, exe, box);
	tun_get_argv(box[i], exe);
	e = tun_get_infile(box[i], exe);
	if (e)
		e = tun_get_outfile(box[i], exe);
	tun_flush_subset(&box[i]);
	tun_clear_process(exe);
}