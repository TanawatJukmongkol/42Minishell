/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_parent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/04 20:20:04 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	sb_single_mom(t_token_stream *subset, t_exec *exe)
{
	int	e;

	e = tun_init_exec_child(exe, subset);
	if (e == 1)
	{
		e &= tun_redirct(exe->infile, exe->in_len, STDIN_FILENO);
		e &= tun_redirct(exe->outfile, exe->out_len, STDOUT_FILENO);
	}
	tun_clean_child(exe);
	if (e)
	{
		if (tun_builin_handler(exe->argv[0], exe->argv, exe->_info) == -1)
		{
			e = fork();
			if (e == 0)
			{
				execve(exe->argv[0], exe->argv, exe->_info->_envp.env);
				heap_purge(&exe->_info->_mem);
				tun_child_exit(&exe->_info->_mem, errno);
			}	
		}
	}
}

static void	sb_big_wait(int *pid, int n)
{
	int	i;
	int	stat;
	int	e;

	i = 0;
	while (i < n)
	{
		if (pid[i] != -1)
		{
			e = tun_waitpid(pid[i], &stat, WUNTRACED, ERR_MSG);
			if (e != -1)
				errno = WEXITSTATUS(stat) % 255;
		}
		i++;
	}
}

void	tun_parent_process(t_main *info)
{
	size_t			i;
	int				*pid_box;
	t_token_stream	*token_box;
	t_exec			exe;

	i = 0;
	exe = tun_exec_init();
	token_box = tun_split_token(info, &exe._pipes.n);
	if (token_box == NULL)
		return (perror(ERR_MSG), ft_exit(&info->_mem, ENOMEM));
	if (tun_init_exec_parent(&exe, info) == 0)
		return (perror(ERR_MSG), ft_exit(&info->_mem, ENOMEM));
	if (exe._pipes.n == 0)
		sb_single_mom(&token_box[0], &exe);
	else
	{
		pid_box = ft_malloc(sizeof(int), exe._pipes.n + 1, &info->_mem, NULL);
		if (pid_box == NULL)
			return (perror(ERR_MSG), ft_exit(&info->_mem, ENOMEM));
		while (i < exe._pipes.n + 1)
		{
			pid_box[i] = tun_fork(ERR_MSG);
			if (pid_box[i] == 0)
				return (tun_child_process(&token_box[i], &exe, i));
			i++;
		}
		tun_close_pipe(info, &exe._pipes);
	}
	sb_big_wait(pid_box, exe._pipes.n);
	heap_free(&info->_mem, token_box);
	heap_free(&info->_mem, pid_box);
}