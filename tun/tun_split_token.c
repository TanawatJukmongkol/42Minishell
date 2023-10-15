/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 04:11:53 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

static int	sb_count_pipe(t_token_stream run)
{
	int	pipe_n;

	pipe_n = 0;
	while (run.begin != NULL)
	{
		pipe_n += run.begin->type == __pipe;
		run.begin = run.begin->next;
	}
	return (pipe_n);
}

void	tun_free_token_box(t_token_stream *box, size_t pipe_n)
{
	size_t	i;

	i = 0;
	if (box == NULL)
		return ;
	while (i < pipe_n + 1)
	{
		ft_tokenfree(&box[i]);
		i++;
	}
	free(box);
}

static void	sb_token_join(t_token_stream *out, t_token_stream *in)
{
	if (out->begin == NULL)
	{
		out->begin = in->begin;
		out->last = in->begin;
	}
	else
	{
		out->last->next = in->begin;
		out->last = out->last->next;
	}
}

static void	sb_token_manage(t_token_stream *out, t_token_stream *in)
{
	t_token	*tmp;

	out->begin = NULL;
	out->last = NULL;
	while (in->begin != NULL)
	{
		tmp = in->begin->next;
		in->begin->next = NULL;
		if (in->begin->type == __pipe)
		{
			free(in->begin->value);
			free(in->begin);
			in->begin = tmp;
			return ;
		}
		sb_token_join(out, in);
		in->begin = tmp;
	}
}

t_token_stream	*tun_split_token(t_main *info, size_t *pipe_n)
{
	size_t			i;
	t_token_stream	*box;

	i = 0;
	*pipe_n = sb_count_pipe(info->_token);
	box = malloc(sizeof(t_token_stream) * (*pipe_n + 1));
	if (box == NULL)
		return (NULL);
	while (i < *pipe_n + 1)
	{
		sb_token_manage(&box[i], &info->_token);
		i++;
	}
	return (box);
}
