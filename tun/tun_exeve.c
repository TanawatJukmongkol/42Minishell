/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exeve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 03:53:53 by tponutha         ###   ########.fr       */
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
		errno = err_no;
		free(full_cmd);
		return (cmd);
	}
	return (full_cmd);
}

static int	sb_relative(char *cmd, char *path)
{
	int	err;

	err = errno;
	if (path == NULL)
		return (1);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (1);
	if (access(cmd, F_OK) != -1)
		return (1);
	errno = err;
	return (0);
}

static char	*sb_find_cmd(char *cmd, char *path, t_main *info)
{
	int		i;
	char	*full_cmd;
	char	**path_set;

	i = 0;
	if (sb_relative(cmd, path))
		return (cmd);
	else if (cmd[0] == '~')
		return (ft_realpath(cmd, info));
	path_set = ft_split(path, ':');
	if (path_set == NULL)
		return (NULL);
	while (path_set[i] != NULL)
	{
		full_cmd = sb_pathjoin(cmd, path_set[i]);
		if (full_cmd == NULL || full_cmd != cmd)
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

void	tun_execve(t_exec *exe, int e)
{
	char	*full_path;
	char	*path;

	if (e == 0 || exe->argv[0] == NULL)
		return ;
	if (tun_builtin_child(exe) != -1)
		return ;
	path = ft_getenv(&exe->_info->_envp, "PATH");
	full_path = sb_find_cmd(exe->argv[0], path, exe->_info);
	if (full_path == NULL)
		return ;
	if (path != NULL && !sb_relative(full_path, path))
		return (tun_cmd_perror(exe, ": command not found\n"));
	if (access(full_path, X_OK) != -1)
		execve(full_path, exe->argv, exe->_info->_envp.env);
	else
		tun_file_perror("minishell: ", exe->argv[0]);
	free(full_path);
}
