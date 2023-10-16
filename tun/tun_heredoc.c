/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 03:06:57 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_heredoc_ignore(t_exec *exe, size_t del_len, int j)
{
	char	*line;
	size_t	len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && errno != ENOMEM)
	{
		len = ft_strclen(line, '\n');
		if (tun_delimeter(exe->delimeter[j], line, del_len, len))
		{
			free(line);
			return (1);
		}
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	return (errno != ENOMEM);
}

static int	sb_close_heredoc(char *line, int e, int pipes[2])
{
	free(line);
	if (errno != ENOMEM)
		e = tun_dup2(pipes[0], STDIN_FILENO) != 1;
	close(pipes[0]);
	close(pipes[1]);
	return (e);
}

static int	sb_heredoc(t_exec *exe, size_t del_len, int j)
{
	int		fd_pipe[2];
	int		e;
	char	*line;
	size_t	len;

	e = 1;
	if (pipe(fd_pipe) == -1)
		return (0);
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && errno != ENOMEM)
	{
		len = ft_strclen(line, '\n');
		if (tun_delimeter(exe->delimeter[j], line, del_len, len))
			break ;
		ft_putstr_fd(line, fd_pipe[1]);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	return (sb_close_heredoc(line, e, fd_pipe));
}

/*
0 = fail
1 = success
*/

int	tun_heredoc(t_exec *exe)
{
	int		i;
	int		pos;
	int		e;
	int		j;

	i = 1;
	j = 0;
	pos = tun_find_last_heredoc(exe->infile, exe->in_len);
	if (pos == 0)
		return (1);
	while (i <= pos)
	{
		if (exe->infile[i] == STDIN_FILENO && i != pos)
		{
			e = sb_heredoc_ignore(exe, ft_strlen(exe->delimeter[j]), j);
			j++;
		}
		else if (exe->infile[i] == STDIN_FILENO && i == pos)
			e = sb_heredoc(exe, ft_strlen(exe->delimeter[j]), j);
		i++;
	}
	return (e);
}
