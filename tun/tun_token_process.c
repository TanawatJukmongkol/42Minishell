/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_token_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/08 20:41:04 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_count_token(t_token_stream subset, t_exec *exe, int *del_len)
{
	int		argv_len;
	
	argv_len = 0;
	*del_len = 0;
	exe->in_len = 0;
	exe->out_len = 0;
	while (subset.begin != NULL)
	{
		if (subset.begin->type == __redirr_in || subset.begin->type == __here_doc)
		{
			exe->in_len++;
			*del_len += subset.begin->type == __here_doc;
		}
		else if (subset.begin->type == __redirr_in || subset.begin->type == __here_doc)
			exe->out_len++;
		else if (subset.begin->type == __argv || subset.begin->type == __cmd)
			argv_len++;
		subset.begin = subset.begin->next;
	}
	return (argv_len);
}

static void	sb_get_argv(t_token *node, t_exec *exe, int *argv_i)
{
	if (!(node->type == __argv || node->type == __cmd))
		return ;
	exe->argv[*argv_i] = node->value;
	(*argv_i)++;
}

static int	sb_get_infile(t_token *node, t_exec *exe, int *in_i, int err)
{
	if (err != 1)
		return (0);
	else if (node->type == __redirr_in)
	{
		exe->infile[in_i[0]] = tun_open(node->value, O_RDONLY, 0644);
		free(node->value);
		node->value = NULL;
	}
	else if (node->type == __here_doc)
	{
		exe->infile[in_i[0]] = STDIN_FILENO;
		exe->delimeter[in_i[1]] = node->value;
		in_i[1]++;
	}
	else
		return (1);
	if (exe->infile[*in_i] == -1)
		return (0);
	in_i[0]++;
	return (1);
}

static int	sb_get_outfile(t_token *node, t_exec *exe, int *out_i, int err)
{
	if (err != 1)
		return (0);
	if (!(node->type == __redirr_append || node->type == __redirr_trunc))
		return (1);
	if (node->type == __redirr_append)
		exe->outfile[*out_i] = tun_open(node->value, O_CREAT | O_APPEND, 0644);
	else
		exe->outfile[*out_i] = tun_open(node->value, O_CREAT | O_TRUNC, 0644);
	free(node->value);
	node->value = NULL;
	if (exe->outfile[*out_i] == -1)
		return (0);
	(*out_i)++;
	return (1);
}

static int	sb_token_to_val(t_token_stream *subset, t_exec *exe)
{
	int		argv_i;
	int		in_i[2];
	int		out_i;
	int		fd_err;
	t_token	*tmp;

	argv_i = 0;
	ft_memset(in_i, 0, sizeof(int) * 2);
	out_i = 0;
	fd_err = 1;
	while (subset->begin != NULL)
	{
		sb_get_argv(subset->begin, exe, &argv_i);
		fd_err = sb_get_infile(subset->begin, exe, in_i, fd_err);
		fd_err = sb_get_outfile(subset->begin, exe, &out_i, fd_err);
		tmp = subset->begin;
		subset->begin = subset->begin->next;
		if (tmp->value != NULL && (tmp->type != __cmd \
			|| tmp->type != __argv || tmp->type != __here_doc))
			free(tmp->value);
		free(tmp);
	}
	return (fd_err);
}

/*
-1 = memory error (exit now)
0 = file error (don't run redirect & exeve)
1 = no error
*/

int	tun_token_process(t_token_stream *subset, t_exec *exe)
{
	int	argv_len;
	int	del_len;

	argv_len = sb_count_token(*subset, exe, &del_len);
	exe->argv = malloc(sizeof(char *) * (argv_len + 1));
	exe->infile = malloc(sizeof(int) * exe->in_len);
	exe->outfile = malloc(sizeof(int) * exe->out_len);
	exe->delimeter = malloc(sizeof(char *) * (del_len + 1));
	if (exe->argv == NULL || exe->infile == NULL \
		|| exe->outfile == NULL || exe->delimeter == NULL)
	{
		free(exe->argv);
		free(exe->infile);
		free(exe->outfile);
		free(exe->delimeter);
		return (-1);
	}
	return (sb_token_to_val(subset, exe));
}