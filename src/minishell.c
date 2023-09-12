/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 22:23:37 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
	(void)(envp);
	t_stackheap		mem;
	char			*prompt;
	char			*line;
	t_token_stream	stream;
	t_token_stream	output;

	heap_init(&mem);
	while (1)
	{
		char	*cwd = ft_getcwd(&mem);
		prompt = ft_strjoin(cwd, "> ");
		free(cwd);
		line = ft_readline(prompt, &mem);
		free(prompt);
		if (!line || !*line)
			continue ;
		lexer(&stream, line);
		// parser(&output, &stream);

		output = stream;
		for (t_token *i=output.begin; i; i = i->next)
		{
			switch (i->type)
			{
				case __none:
					printf("%-14s", "none"); break;
				case __pipe:
					printf("%-14s", "pipe"); break;
				case __redirr_in:
					printf("%-14s", "redirr_in"); break;
				case __here_doc:
					printf("%-14s", "here_doc"); break;
				case __redirr_trunc:
					printf("%-14s", "redirr_trunc"); break;
				case __redirr_append:
					printf("%-14s", "redirr_append"); break;
				case __cmd:
					printf("%-14s", "cmd"); break;
				case __argv:
					printf("%-14s", "argv"); break;
			}
			printf("-> %s\n", i->value);
		}
		ft_tokenfree(&stream);
		// ft_tokenfree(&output);
	}
	return (0);
}

