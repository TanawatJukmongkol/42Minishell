/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/11 16:45:17 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
	(void)(envp);
	char			*prompt;
	char			*line;
	t_token_stream	stream;
	t_token_stream	output;

	while (1)
	{
		char	*cwd = ft_getcwd();
		prompt = ft_strjoin(cwd, "> ");
		free(cwd);
		line = ft_readline(prompt);
		free(prompt);
		if (!line || !*line)
			continue ;
		lexer(&stream, line);
		// parser(&output, &stream);

		output = stream;
		for (t_token *i=output.begin; i; i = i->next)
			printf("%d:%s\n", i->type, i->value);
		ft_tokenfree(&stream);
		// ft_tokenfree(&output);
	}
	return (0);
}

