/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:41 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 21:54:11 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	quote_remove(t_token_stream *s, t_token *t, void *vars)
{
	int		q;
	int		dbq;
	char	*res;
	size_t	indx;
	size_t	indx_res;

	(void)(vars);
	q = 0;
	dbq = 0;
	indx = 0;
	indx_res = 0;
	res = ft_calloc(ft_strlen(t->value) + 1, 1);
	while (t->value[indx])
	{
		if (!q && t->value[indx] == '\"')
			dbq = !dbq;
		else if (!dbq && t->value[indx] == '\'')
			q = !q;
		else
			res[indx_res++] = t->value[indx];
		indx++;
	}
	ft_token(s, t->type)->value = res;
}

void	stage4_tokenizer(t_token_stream *dst, t_token_stream *stage4)
{
	while (stage4->begin)
		ft_token_consume(dst, stage4, quote_remove, NULL);
}
