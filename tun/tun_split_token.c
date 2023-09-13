/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_split_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:08:33 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/14 01:23:21 by tponutha         ###   ########.fr       */
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

void	tun_free_token_box(void *tokens)
{
	size_t		i;
	t_token_set	*set;
	t_token		*tmp;

	i = 0;
	set = (t_token_set *)tokens;
	while (i < set->n)
	{
		while (set->token_set[i].begin)
		{
			tmp = set->token_set->begin->next;
			heap_free(set->mem, set->token_set[i].begin);
			set->token_set->begin = tmp;
		}
		i++;
	}
	free(set->token_set);
}

static void	sb_token_abuse(t_token_stream *out, t_main *info, int *i)
{
	if (*i == 0)
	{
		out->begin = info->_token.begin;
		out->last = info->_token.begin;
		(*i)++;
	}
	else
	{
		out->last->next = info->_token.begin;
		out->last = out->last->next;
	}
	out->last->next = NULL;
}

static void	sb_token_manage(t_token_stream *out, t_main *info)
{
	int		i;
	t_token	*tmp;

	i = 0;
	while (info->_token.begin != NULL)
	{
		if (info->_token.begin->type == __pipe)
		{
			tmp = info->_token.begin->next;
			heap_free(&info->_mem, info->_token.begin);
			info->_token.begin = tmp;
			break ;
		}
		sb_token_abuse(out, info, &i);
		info->_token.begin = info->_token.begin->next;
	}
}

t_token_stream	*tun_split_token(t_main *info, size_t *pipe_n)
{
	size_t			i;
	t_token_stream	*box;

	i = 0;
	*pipe_n = sb_count_pipe(info->_token);
	box = malloc(sizeof(t_token_stream) * (*pipe_n + 1));
	if (box  == NULL)
		return (NULL);
	while (i < *pipe_n + 1)
	{
		sb_token_manage(&box[i], info);
		i++;
	}
	if (heap_push(&info->_mem, box, tun_free_token_box) == -1)
		return (NULL);
	return (box);
}