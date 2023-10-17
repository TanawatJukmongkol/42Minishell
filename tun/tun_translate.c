/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/17 12:03:23 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_infile(t_token *node, t_exec *exe, int *i, int *j)
{
	int	err;

	err = 1;
	if (node->type == __redirr_in)
	{
		exe->infile[*i] = tun_open(node->value, O_RDONLY, 0644);
		err = exe->infile[*i] != -1;
	}
	else if (node->type == __here_doc)
	{
		exe->infile[*i] = STDIN_FILENO;
		exe->delimeter[*j] = node->value;
		(*j)++;
	}
	*i += node->type == __redirr_in || node->type == __here_doc;
	return (err);
}

int	tun_get_infile(t_token_stream subset, t_exec *exe)
{
	int	i;
	int	j;
	int	err;

	i = 1;
	j = 0;
	err = 1;
	if (exe->in_len == 0)
		return (err);
	exe->infile[0] = STDIN_FILENO;
	while (subset.begin != NULL && err == 1 \
			&& errno != ENOMEM && i < exe->in_len)
	{
		if (subset.begin->type == __redirr_in \
			|| subset.begin->type == __here_doc)
			err = sb_infile(subset.begin, exe, &i, &j);
		subset.begin = subset.begin->next;
	}
	exe->delimeter[j] = NULL;
	return (err);
}

static int	sb_outfile(t_token *node, t_exec *exe, int *i, int err)
{
	if (node->type == __redirr_append)
	{
		exe->outfile[*i] = tun_open(node->value, \
							O_WRONLY | O_APPEND | O_CREAT, 0644);
		err = exe->outfile[*i] != -1;
	}
	else if (node->type == __redirr_trunc)
	{
		exe->outfile[*i] = tun_open(node->value, \
								O_WRONLY | O_TRUNC | O_CREAT, 0644);
		err = exe->outfile[*i] != -1;
	}
	*i += node->type == __redirr_append || node->type == __redirr_trunc;
	return (err);
}

int	tun_get_outfile(t_token_stream subset, t_exec *exe)
{
	int	i;
	int	err;

	i = 1;
	err = 1;
	if (exe->out_len == 0)
		return (err);
	exe->outfile[0] = STDOUT_FILENO;
	while (subset.begin != NULL && err == 1 \
			&& errno != ENOMEM && i < exe->out_len)
	{
		err = sb_outfile(subset.begin, exe, &i, err);
		subset.begin = subset.begin->next;
	}
	return (err);
}

int	tun_get_argv(t_token_stream subset, t_exec *exe)
{
	int	i;

	i = 0;
	while (subset.begin != NULL)
	{
		if (subset.begin->type == __cmd || subset.begin->type == __argv)
		{
			if (subset.begin->value[0] == '~')
				exe->argv[i] = ft_realpath(subset.begin->value, exe->_info);
			else
				exe->argv[i] = ft_strdup(subset.begin->value);
			if (exe->argv[i] == NULL)
				return (0);
			i++;
		}
		subset.begin = subset.begin->next;
	}
	exe->argv[i] = NULL;
	return (1);
}
