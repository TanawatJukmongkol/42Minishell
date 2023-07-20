/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:12 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/20 18:00:01 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ittr(t_token_stream *s, t_token *t)
{
	(void)(t);
	// ft_token(s, __none)->value = ft_strjoin("replaced -> ", t->value);
	ft_token(s, __pipe)->value = ft_strdup("replaced!");
}

int	main(void)
{
	t_token_stream	stream;
	t_token_stream	stream2;
	// t_token_stream	stream3;

	stream.begin = NULL;
	stream2.begin = NULL;
	ft_token(&stream, __none)->value = ft_strdup("This node will be replaced!");
	ft_token(&stream, __none)->value = ft_strdup("Hello, world!");
	ft_token(&stream, __none)->value = ft_strdup("why?");
	ft_token_consume(&stream2, &stream, ittr);
	// ft_token(&stream3, __none)->value = ft_strdup("lol");

	t_token *tmp;
	for (t_token *t = stream.begin; t != NULL; t = tmp)
	{
		tmp = t->next;
		printf("[%p:%s]->[%p]\n", t, t->value, t->next);
		free(t->value);
		free(t);
	}
	return (0);
}
