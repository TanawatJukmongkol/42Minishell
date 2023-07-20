/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stream_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:30:45 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/19 19:55:15 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	ft_stream_join(t_token_stream *dst, t_token_stream *src)
{
	(dst->last)->next = src->begin;
	dst->last = src->last;
	src->begin = NULL;
	src->last = NULL;
}
