/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/13 22:38:02 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_open_infile(t_token_stream *subset, t_exec *exe)
{
	int		i;
	int		err;
	t_token	*run;

	i = 1;
	err = 1;
	exe->infile[0] = STDIN_FILENO;
	run = subset->begin;
	while (run != NULL)
	{
		if (run->type == __redirr_in)
		{
			exe->infile[i] = tun_open(run->value, O_RDONLY, 0644);
			if (exe->infile[i] == -1)
				err = 0;
		}
		else if (run->type == __here_doc)
		{
			exe->infile[i] = STDIN_FILENO;
			exe->delimeter = ft_strdup_heap(run->value, &exe->_info->_mem);
			err = exe->delimeter != NULL;
		}
		i += run->type == __redirr_in || run->type == __here_doc;
		run = run->next;
	}
	return (err);
}

int	tun_get_infile(t_token_stream *subset, t_exec *exe)
{
	int	err;

	err = 1;
	exe->in_len = tun_count_type(subset, __redirr_in, __here_doc);
	if (exe->in_len == 0)
		exe->infile = NULL;
	else
	{
		exe->infile = ft_malloc(sizeof(int), exe->in_len + 2, &exe->_info->_mem, NULL);
		if (exe->infile == NULL)
		{
			exe->in_len = -1;
			return (0);
		}
		err = sb_open_infile(subset, exe);
	}
	return (1);
}

static int	sb_open_outfile(t_token_stream *subset, t_exec *exe)
{
	int		i;
	int		err;
	t_token	*run;

	i = 1;
	err = 1;
	exe->outfile[0] = STDOUT_FILENO;
	run = subset->begin;
	while (run != NULL)
	{
		if (run->type == __redirr_append)
		{
			exe->outfile[i] = tun_open(run->value, \
								O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (exe->infile[i] == -1)
				err = 0;
		}
		else if (run->type == __redirr_trunc)
		{
			exe->outfile[i] = tun_open(run->value, \
								O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (exe->infile[i] == -1)
				err = 0;
		}
		i += run->type == __redirr_append || run->type == __redirr_trunc;
		run = run->next;
	}
	return (err);
}

int	tun_get_outfile(t_token_stream *subset, t_exec *exe)
{
	int	err;

	err = 1;
	exe->out_len = tun_count_type(subset, __redirr_append, __redirr_trunc);
	if (exe->out_len == 0)
		exe->outfile = NULL;
	else
	{
		exe->outfile = ft_malloc(sizeof(int), exe->out_len + 2, &exe->_info->_mem, NULL);
		if (exe->outfile == NULL)
		{
			exe->out_len = -1;
			return (0);
		}
		err = sb_open_outfile(subset, exe);
	}
	return (1);
}