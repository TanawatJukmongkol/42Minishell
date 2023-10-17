/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/18 02:08:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

// /*
// 0 = fail
// 1 = success
// */

// int	tun_heredoc(t_exec *exe)
// {
// 	int		i;
// 	int		pos;
// 	int		e;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	pos = tun_find_last_heredoc(exe->infile, exe->in_len);
// 	if (pos == 0)
// 		return (1);
// 	while (i <= pos)
// 	{
// 		if (exe->infile[i] == STDIN_FILENO && i != pos)
// 		{
// 			e = sb_heredoc_ignore(exe, ft_strlen(exe->delimeter[j]), j);
// 			j++;
// 		}
// 		else if (exe->infile[i] == STDIN_FILENO && i == pos)
// 			e = sb_heredoc(exe, ft_strlen(exe->delimeter[j]), j);
// 		i++;
// 	}
// 	return (e);
// }

// static int	sb_close_heredoc(char *line, int e, int *pipes)
// {
// 	free(line);
// 	if (errno != ENOMEM)
// 		e = tun_dup2(pipes[0], STDIN_FILENO) != 1;
// 	close(pipes[0]);
// 	close(pipes[1]);
// 	return (e);
// }

static int	sb_heredoc(int *pipes, char *del, size_t del_len)
{
	int		e;
	char	*line;
	size_t	len;

	e = 1;
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && errno != ENOMEM)
	{
		len = ft_strclen(line, '\n');
		if (tun_delimeter(del, line, del_len, len))
			break ;
		ft_putstr_fd(line, pipes[1]);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (e);
}

static int	sb_heredoc_ignore(char *del, size_t del_len)
{
	char	*line;
	size_t	len;

	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && errno != ENOMEM)
	{
		len = ft_strclen(line, '\n');
		if (tun_delimeter(del, line, del_len, len))
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

static int	sb_run_heredoc(t_token_stream sub, int *p, char *str)
{
	int		err;
	size_t	del_len;

	err = 1;
	while (sub.begin != NULL && err == 1)
	{
		if (sub.begin->value != str && sub.begin->type == __here_doc)
		{
			del_len = ft_strlen(sub.begin->value);
			err = sb_heredoc_ignore(sub.begin->value, del_len);
		}
		else if (sub.begin->value == str && sub.begin->type == __here_doc)
		{
			del_len = ft_strlen(sub.begin->value);
			err = sb_heredoc(p, sub.begin->value, del_len);
		}
		sub.begin = sub.begin->next;
	}
	return (err);
}

/*
0 = fail
1 = success
*/

int	tun_heredoc(t_token_stream *box, size_t pipe_n, t_exec *exe)
{
	size_t	i;
	char	*str;
	int		err;

	i = 0;
	err = 1;
	while (i <= pipe_n && err == 1)
	{
		str = tun_last_delimeter(box[i]);
		if (str == NULL)
		{
			tun_close(exe->_heredoc.box[i][0]);
			tun_close(exe->_heredoc.box[i][1]);
			exe->_heredoc.box[i][0] = -1;
			exe->_heredoc.box[i][1] = -1;
		}
		else
			err = sb_run_heredoc(box[i], exe->_heredoc.box[i], str);
		i++;
	}
	return (err);
}
