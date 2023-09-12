/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage2_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:25 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 19:11:40 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	meta_pipe(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, "|", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (*next_match)
			ft_token(s, __pipe)->value = ft_strdup("|");
		if (!*next_match)
			break ;
		ptr = ++next_match;
	}
}

void	meta_redirr_in(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	if (t->type == __here_doc)
		ft_token(s, t->type)->value = ft_strdup("<<");
	else
	{
		ptr = t->value;
		next_match = ptr;
		while (1)
		{
			next_match = get_next_qoute(next_match, "<", 1);
			len = next_match - ptr;
			if (len)
				ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
			if (*next_match)
				ft_token(s, __redirr_in)->value = ft_strdup("<");
			if (!*next_match)
				break ;
			ptr = ++next_match;
		}
	}
}

void	meta_redirr_out_trunc(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	if (t->type == __redirr_append)
		ft_token(s, t->type)->value = ft_strdup(">>");
	else
	{
		ptr = t->value;
		next_match = ptr;
		while (1)
		{
			next_match = get_next_qoute(next_match, ">", 1);
			len = next_match - ptr;
			if (len)
				ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
			if (*next_match)
				ft_token(s, __redirr_trunc)->value = ft_strdup(">");
			if (!*next_match)
				break ;
			ptr = ++next_match;
		}
	}
}

void	stage2_tokenizer(t_token_stream *dst, t_token_stream *stage2)
{
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_heredoc);
	while(dst->begin)
		ft_token_consume(stage2, dst, meta_redirr_out_append);
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_pipe);
	while(dst->begin)
		ft_token_consume(stage2, dst, meta_redirr_in);
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_redirr_out_trunc);
}

