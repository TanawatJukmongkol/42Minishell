/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/05 22:39:35 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*get_next_qoute(char *str, char *match)
{
	int		q;
	int		dbq;

	q = 0;
	dbq = 0;
	while (*str)
	{
		if (*str == '\"' && *str != '\'')
			dbq = !dbq;
		if (*str == '\'' && *str != '\"')
			q = !q;
		str++;
		if (!ft_strncmp(str, match, ft_strlen(
						match)) && !q && !dbq)
			break ;
	}
	return (str);
}

void white_space(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_space;
	size_t	len;

	ptr = t->value;
	next_space = ptr;
	len = 0;
	while (*next_space)
	{
		next_space = get_next_qoute(next_space, " ");
		len = next_space - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		ptr = next_space + 1;
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
	t_token_stream	stage2;
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
