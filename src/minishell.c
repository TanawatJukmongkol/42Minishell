/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:12 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/05 09:32:21 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void white_space(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_space;
	size_t	len;

	ptr = t->value;
	len = 0;
	while (1)
	{
		next_space = ft_strchr(ptr, ' ');
		if (!next_space)
			next_space = ft_strchr(ptr, '\0');
		len = next_space - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len); 
		ptr = next_space + 1;
		if (!*next_space)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
	(void)(envp);
	char			*prompt;
	char			*line;
	t_token_stream	stage1;
	t_token_stream	output;

	stage1.begin = NULL;
	prompt = ft_strjoin(ft_getcwd(), "> ");
	line = ft_readline(prompt);
	free(prompt);
	if (!prompt)
		return (0);
	ft_token(&stage1, __none)->value = line;
	ft_token_consume(&output, &stage1, white_space);
	for (t_token *i=output.begin; i; i = i->next)
		printf("%s\n", i->value);
	return (0);
}

