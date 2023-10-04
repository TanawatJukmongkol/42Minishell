/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_consume.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:30:19 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/04 18:27:21 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	ft_token_consume(t_token_stream *dst, t_token_stream *src,
	void (*fn)(t_token_stream *s,t_token *t, void *vars), void *vars)
{
	t_token_stream	tmp;
	t_token			*begin_next;

	if (!dst || !src || !src->begin)
		return ;
	tmp.begin = NULL;
	fn(&tmp, src->begin, vars);
	begin_next = src->begin->next;
	free(src->begin->value);
	free(src->begin);
	src->begin = begin_next;
	if (!dst->begin)
		dst->begin = tmp.begin;
	else
		dst->last->next = tmp.begin; // segfault here
	dst->last = tmp.last;
}

// Suggest : i think it's segfault due to you forget to init last
