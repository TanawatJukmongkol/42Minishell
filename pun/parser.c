/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:42 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 20:51:46 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

void	rearrange_token_heredoc(t_token_stream *s, t_token *t)
{
	t_token	*tmp;
	if (t->type != __here_doc)
	{
		if (t->next && t->type == __none && t->next->type == __here_doc)
		{
			if (t->next && t->next->next)
			{
				ft_token(s, __here_doc)->value = ft_strdup(t->next->next->value);
				tmp = t->next;
				t->next = t->next->next;
				free((tmp)->value);
				free(tmp);
				tmp = t->next;
				t->next = t->next->next;
				free((tmp)->value);
				free(tmp);
			}
			ft_token(s, __cmd)->value = ft_strdup(t->value);
		}
		else
			ft_token(s, t->type)->value = ft_strdup(t->value);
	}
	else
	{
		if (t->next)
		{
			ft_token(s, __here_doc)->value = ft_strdup(t->next->value);
			tmp = t->next;
			t->next = t->next->next;
			free((tmp)->value);
			free(tmp);
		}
		if (t->next)
		{
			ft_token(s, __cmd)->value = ft_strdup(t->next->value);
			tmp = t->next;
			t->next = t->next->next;
			free((tmp)->value);
			free(tmp);
		}
	}
}

void	rearrange_token_redirr_in(t_token_stream *s, t_token *t)
{
	t_token	*tmp;
	if (t->type != __redirr_in)
	{
		if (t->next && t->type == __none && t->next->type == __redirr_in)
		{
			if (t->next && t->next->next)
			{
				ft_token(s, __cmd)->value = ft_strdup(t->next->next->value);
				tmp = t->next;
				t->next = t->next->next;
				free((tmp)->value);
				free(tmp);
				tmp = t->next;
				t->next = t->next->next;
				free((tmp)->value);
				free(tmp);
				ft_token(s, __redirr_in)->value = ft_strdup(t->value);
			}
		}
		else
			ft_token(s, t->type)->value = ft_strdup(t->value);
	}
	else
	{
		if (t->next)
		{
			ft_token(s, __redirr_in)->value = ft_strdup(t->next->value);
			tmp = t->next;
			t->next = t->next->next;
			free((tmp)->value);
			free(tmp);
		}
		if (t->next)
		{
			ft_token(s, __cmd)->value = ft_strdup(t->next->value);
			tmp = t->next;
			t->next = t->next->next;
			free((tmp)->value);
			free(tmp);
		}
	}
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	t_token_stream	stage1;
	//t_token_stream	stage2;

	stage1.begin = NULL;
	//stage2.begin = NULL;
	while (input->begin)
		ft_token_consume(&stage1, input, rearrange_token_heredoc);
	while (stage1.begin)
		ft_token_consume(output, &stage1, rearrange_token_redirr_in);
}

