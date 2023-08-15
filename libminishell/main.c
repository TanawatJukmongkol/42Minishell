/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/13 07:11:31 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// void fn(t_token_stream *s, t_token *t)
// {
// 	ft_token(s, t->type)->value = ft_substr(t->value, 0,
// 		ft_strchr(t->value, ' ') - t->value
// 	);
// }

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
	// t_token_stream	stage1;
	// t_token_stream	stage2;

	// stage1.begin = NULL;
	// stage2.begin = NULL;
	// ft_token(&stage1, __none)->value = ft_strdup("This node will be replaced!");
	// ft_token(&stage1, __none)->value = ft_strdup("Hello,world!");
	// ft_token(&stage1, __none)->value = ft_strdup("why?");
	// ft_token_consume(&stage2, &stage1, fn);
	// ft_token_consume(&stage2, &stage1, fn);

	// printf("---[ stage 1 ]---\n");
	// for (t_token *t = stage1.begin; t; t = t->next)
	// 	printf("[%p] token: \"%s\"\n", t, t->value);
	// printf("---[ stage 2 ]---\n");
	// for (t_token *t = stage2.begin; t; t = t->next)
	// 	printf("[%p] token: \"%s\"\n", t, t->value);

	// ft_tokenfree(&stage1);
	// ft_tokenfree(&stage2);

	t_envp	env;

	ft_initenv(&env, envp);
	ft_genenv(&env);

	for (size_t indx = 0; indx < env.len; indx++)
	{
		printf("%s\n", env.cache[indx]);
	}

	// for (t_envnode *n = env.begin; n; n = n->next)
	// {
	// 	printf("%s:%s\n", n->key, n->value);
	// }

	return (0);
}
