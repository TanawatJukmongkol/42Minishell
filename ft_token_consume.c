/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_consume.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:30:19 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 20:51:34 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	ft_token_consume(t_token_stream *dst, t_token_stream *src,
	void (*fn)(t_token_stream *s, t_token *t, void *vars), void *vars)
{
	t_token_stream	tmp;
	t_token			*begin_next;

	if (!fn || !dst || !src || !src->begin)
		return ;
	tmp.begin = NULL;
	tmp.last = NULL;
	fn(&tmp, src->begin, vars);
	begin_next = src->begin->next;
	free(src->begin->value);
	free(src->begin);
	src->begin = begin_next;
	if (!tmp.begin)
		return ;
	if (!dst->begin)
		dst->begin = tmp.begin;
	else
		dst->last->next = tmp.begin;
	dst->last = tmp.last;
}
