/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:20 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 13:36:22 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	init_table(t_cmd_table *table)
{
	table->cmd = NULL;
	table->search_argv = 0;
	table->infile.begin = NULL;
	table->infile.last = NULL;
	table->outfile.begin = NULL;
	table->outfile.last = NULL;
	table->argv.begin = NULL;
	table->argv.last = NULL;
}

void	rm_next(t_token *t)
{
	t_token	*tmp;

	if (!t->next)
		return ;
	tmp = t->next;
	t->next = t->next->next;
	free(tmp->value);
	free(tmp);
}

void	append_table(t_token_stream *dst, t_token_stream *src)
{
	if (!dst->begin)
	{
		dst->begin->next = src->begin;
		dst->last = src->last;
	}
	dst->last->next = src->begin;
	dst->last = src->last;
}
