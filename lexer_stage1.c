/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:13 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 21:53:18 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	white_space(t_token_stream *s, t_token *t, void *vars)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	(void)(vars);
	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, " ", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (!*next_match)
			break ;
		ptr = ++next_match;
	}
}

void	stage1_tokenizer(t_token_stream *dst,
	t_token_stream *stage1, char *input)
{
	ft_token(stage1, __none)->value = input;
	ft_token_consume(dst, stage1, white_space, NULL);
}
