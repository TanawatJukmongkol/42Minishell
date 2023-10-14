/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:44:28 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 21:00:22 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

t_token	*ft_token(t_token_stream *stream, t_token_type type)
{
	t_token	*new_token;

	if (!stream)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = NULL;
	new_token->next = NULL;
	if (!stream->begin)
	{
		stream->begin = new_token;
		stream->last = stream->begin;
		return (new_token);
	}
	(stream->last)->next = new_token;
	stream->last = (stream->last)->next;
	return (new_token);
}
