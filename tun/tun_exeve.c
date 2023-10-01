/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exeve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/30 18:07:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static char	*sb_pathjoin(char *cmd, char *path)
{
	char	*add_slash;
	char	*full_cmd;
	int		err_no;
	
	add_slash = ft_strjoin(path, "/");
	if (add_slash == NULL)
		return (NULL);
	full_cmd = ft_strjoin(add_slash, cmd);
	free(add_slash);
	if (full_cmd == NULL)
		return (NULL);
	err_no = errno;
	if (access(full_cmd, F_OK) == -1)
	{
		free(full_cmd);
		return (cmd);
	}
	errno = err_no;
	return (full_cmd);
}

static char	*sb_find_cmd(char *cmd, t_main *info)
{
	int		i;
	char	*path;
	char	*full_cmd;
	char	**path_set;

	i = 0;
	path = ft_getenv(&info->_envp, "PATH");
	if (path == NULL)
		return (cmd);
	path_set = ft_split_heap(path, ':', &info->_mem);
	if (path_set == NULL)
		return (NULL);
	while (path_set[i] != NULL)
	{
		full_cmd = sb_pathjoin(cmd, path_set[i]);
		if (full_cmd == NULL)
		{
			heap_free(&info->_mem, path_set);
			return (NULL);
		}
		if (full_cmd != cmd)
			break ;
		i++;
	}
	heap_free(&info->_mem, path_set);
	return (full_cmd);
}

void	tun_execve(t_exec *exe)
{
	// char	**argv;
	char	*full_path;

	// TODO : handle ~/ later na
	full_path = sb_find_cmd(exe->argv[0], exe->_info);
	if (full_path == NULL)
		return ;
	if (full_path != exe->argv[0])
	{
		free(exe->argv[0]);
		exe->argv[0] = full_path;
	}
	execve(exe->argv[0], exe->argv, exe->_info->_envp.env);
	// TODO : put perror here
}