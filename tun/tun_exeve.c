/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exeve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/12 14:43:11 by tponutha         ###   ########.fr       */
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

static char	*sb_find_cmd(char *cmd, char *path)
{
	int		i;
	char	*full_cmd;
	char	**path_set;

	i = 0;
	if (path == NULL || cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	path_set = ft_split(path, ':');
	if (path_set == NULL)
		return (NULL);
	while (path_set[i] != NULL)
	{
		full_cmd = sb_pathjoin(cmd, path_set[i]);
		if (full_cmd == NULL)
		{
			ft_free_split(path_set);
			return (NULL);
		}
		if (full_cmd != cmd)
			break ;
		i++;
	}
	ft_free_split(path_set);
	return (full_cmd);
}

/*
if path is set and not found -> command not found
if path isn't set -> thrown it to access and check for x
*/

void	tun_execve(t_exec *exe)
{
	char	*full_path;
	char	*path;

	// TODO : handle ~/ later na
	if (exe->argv[0] == NULL)
		return ;
	path = ft_getenv(&exe->_info->_envp, "PATH");
	full_path = sb_find_cmd(exe->argv[0], path);
	if (full_path == NULL)
		return ;
	if (full_path != exe->argv[0])
	{
		free(exe->argv[0]);
		exe->argv[0] = full_path;
	}
	if (path != NULL && (exe->argv[0][0] != '.' && exe->argv[0][0] != '/'))
		return (tun_cmd_perror(exe, ": command not found\n"));
	if (access(exe->argv[0], X_OK) != -1)
		execve(exe->argv[0], exe->argv, exe->_info->_envp.env);
	else
		tun_cmd_perror(exe, ": No such file or directory\n");
}