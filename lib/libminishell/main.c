/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/09 20:23:18 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void fn(t_token_stream *s, t_token *t)
{
	ft_token(s, t->type)->value = ft_substr(t->value, 0,
		ft_strchr(t->value, ' ') - t->value
	);
}

int	main(void)
{
	t_token_stream	stage1;
	t_token_stream	stage2;

	stage1.begin = NULL;
	stage2.begin = NULL;
	ft_token(&stage1, __none)->value = ft_strdup("This node will be replaced!");
	ft_token(&stage1, __none)->value = ft_strdup("Hello,world!");
	ft_token(&stage1, __none)->value = ft_strdup("why?");
	ft_token_consume(&stage2, &stage1, fn);
	ft_token_consume(&stage2, &stage1, fn);

	printf("---[ stage 1 ]---\n");
	for (t_token *t = stage1.begin; t; t = t->next)
		printf("[%p] token: \"%s\"\n", t, t->value);
	printf("---[ stage 2 ]---\n");
	for (t_token *t = stage2.begin; t; t = t->next)
		printf("[%p] token: \"%s\"\n", t, t->value);

	ft_tokenfree(&stage1);
	ft_tokenfree(&stage2);

	return (0);
}
