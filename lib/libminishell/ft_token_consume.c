/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_consume.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:30:19 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/20 18:01:03 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	ft_token_consume(t_token_stream *dst, t_token_stream *src, \
	void (*fn)(t_token_stream *stream, t_token *t))
{
	t_token_stream	tmp;
	t_token			*next_token;

	tmp.begin = NULL;
	while (src->begin)
	{
		next_token = src->begin->next;
		fn(&tmp, src->begin);
		if (src->begin->value)
			free(src->begin->value);
		free(src->begin);
		src->begin = next_token;
	}
	ft_stream_join(dst, &tmp);
}
