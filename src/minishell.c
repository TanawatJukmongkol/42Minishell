/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 00:43:17 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	repl(t_token_stream *lex, t_main *info)
{
	t_token_stream	*box;
	size_t			pipe_n;
	char			*line;

	line = ft_readline("minishell> ");
	if (!line)
		return (1);
	if (line[0] != 0)
	{
		lexer(lex, line, *info);
		parser(&info->_token, lex);
		if (info->_token.begin == NULL)
			exit(ft_clear_main(info, 0));
		box = tun_split_token(info, &pipe_n);
		tun_parent_process(info, box, pipe_n);
		tun_free_token_box(box, pipe_n);
	}
	else
		free(line);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_token_stream	lex;
	t_main			info;

	(void)av;
	if (ac != 1)
		return (0);
	if (ft_signal() == 0)
		return (0);
	if (ft_init_main(&info, envp) == -1)
		return (ENOMEM);
	lex.begin = NULL;
	lex.last = NULL;
	while (!repl(&lex, &info))
		;
	printf("exit\n");
	return (ft_clear_main(&info, 0));
}
