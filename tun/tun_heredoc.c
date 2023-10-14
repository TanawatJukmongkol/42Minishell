/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/13 13:48:57 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_delimeter(char *del, char *line, size_t del_len, size_t len)
{
	if (del_len != len)
		return (0);
	if (ft_strncmp(del, line, len) != 0)
		return (0);
	free(line);
	return (1);
}

static int	sb_heredoc_ignore(t_exec *exe, size_t del_len, int j)
{
	char	*line;
	size_t	len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && errno != ENOMEM)
	{
		len = ft_strclen(line, '\n');
		if (sb_delimeter(exe->delimeter[j], line, del_len, len))
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
		if (sb_delimeter(exe->delimeter[j], line, del_len, len))
			break ;
		ft_putstr_fd(line, fd_pipe[1]);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	if (errno != ENOMEM)
	{
		e = tun_dup2(fd_pipe[0], STDIN_FILENO) != -1;
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	return (e);
}

static int	sb_find_last_heredoc(int *infile, int in_len)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < in_len)
	{
		if (infile[i] == STDIN_FILENO)
			pos = i;
		i++;
	}
	return (pos);
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
	pos = sb_find_last_heredoc(exe->infile, exe->in_len);
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