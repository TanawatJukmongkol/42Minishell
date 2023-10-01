/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/01 22:10:20 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_token_stream	lex;
	t_main			info;
	char			*line;

	(void)av;
	if (ac != 1)
		return (0);
	if (ft_init_main(&info, envp) == -1)
	{
		heap_purge(&info._mem);
		return (ENOMEM);
	}
	lex.begin = NULL;
	lex.last = NULL;
	line = ft_readline("minishell>", &info._mem);	
	while (line != NULL)
	{
		lexer(&lex, line);
		parser(&info._token, &lex);
		while (info._token.begin != NULL)
		{
			printf("%d - %s\n", info._token.begin->type, info._token.begin->value);
			info._token.begin = info._token.begin->next;
		}
		heap_free(&info._mem, line);
		line = ft_readline("minishell>", &info._mem);	
	}
	heap_purge(&info._mem);
	return (0);
}