/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/07 05:14:42 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*get_next_qoute(char *str, char *match, int single)
{
	int		q;
	int		dbq;

	q = 0;
	dbq = 0;
	while (*str)
	{
		if (single && *str == '\"' && *str != '\'')
			dbq = !dbq;
		if (*str == '\'' && *str != '\"')
			q = !q;
		if (!ft_strncmp(str, match, ft_strlen(
						match)) && !q && !dbq)
			break ;
		str++;
	}
	return (str);
}

void	white_space(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, " ", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (!*next_match)
			break ;
		ptr = ++next_match;
	}
}

void	meta_heredoc(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, "<<", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (*next_match)
			ft_token(s, __here_doc)->value = ft_strdup("<<");
		if (!*next_match)
			break ;
		next_match += 2;
		ptr = next_match;
	}
}

void	meta_redirr_out_append(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, ">>", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (*next_match)
			ft_token(s, __redirr_append)->value = ft_strdup(">>");
		if (!*next_match)
			break ;
		next_match += 2;
		ptr = next_match;
	}
}

void	meta_pipe(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = get_next_qoute(next_match, "|", 1);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (*next_match)
			ft_token(s, __pipe)->value = ft_strdup("|");
		if (!*next_match)
			break ;
		ptr = ++next_match;
	}
}

void	meta_redirr_in(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	if (t->type == __here_doc)
		ft_token(s, t->type)->value = ft_strdup("<<");
	else
	{
		ptr = t->value;
		next_match = ptr;
		while (1)
		{
			next_match = get_next_qoute(next_match, "<", 1);
			len = next_match - ptr;
			if (len)
				ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
			if (*next_match)
				ft_token(s, __redirr_in)->value = ft_strdup("<");
			if (!*next_match)
				break ;
			ptr = ++next_match;
		}
	}
}

void	meta_redirr_out_trunc(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	if (t->type == __redirr_append)
		ft_token(s, t->type)->value = ft_strdup(">>");
	else
	{
		ptr = t->value;
		next_match = ptr;
		while (1)
		{
			next_match = get_next_qoute(next_match, ">", 1);
			len = next_match - ptr;
			if (len)
				ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
			if (*next_match)
				ft_token(s, __redirr_trunc)->value = ft_strdup(">");
			if (!*next_match)
				break ;
			ptr = ++next_match;
		}
	}
}

void	stage2_tokenizer(t_token_stream *dst, t_token_stream *stage2)
{
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_heredoc);
	while(dst->begin)
		ft_token_consume(stage2, dst, meta_redirr_out_append);
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_pipe);
	while(dst->begin)
		ft_token_consume(stage2, dst, meta_redirr_in);
	while(stage2->begin)
		ft_token_consume(dst, stage2, meta_redirr_out_trunc);
}

int	main(int argc, char **argv, char **envp)
{
	(void)(argc);
	(void)(argv);
	(void)(envp);
	// char			*prompt;
	char			*line = ft_strdup("<file echo \"hello, world!\"|cat>outfile");
	t_token_stream	stage1;
	t_token_stream	stage2;
	t_token_stream	stage3;
	t_token_stream	output;

	stage1.begin = NULL;
	stage2.begin = NULL;
	stage3.begin = NULL;
	/*char	*cwd = ft_getcwd();
	prompt = ft_strjoin(cwd, "> ");
	free(cwd);
	line = ft_readline(prompt);
	free(prompt);*/
	/*if (!prompt)
		return (0);*/
	ft_token(&stage1, __none)->value = line;
	ft_token_consume(&stage2, &stage1, white_space); // Split space
	stage2_tokenizer(&stage3, &stage2); // Split 
	output = stage3;
	
	t_token	*tmp;
	for (t_token *i=output.begin; i; i = tmp)
	{
		tmp = i->next;
		printf("%d:%s\n", i->type, i->value);
		free(i->value);
		free(i);
	}
	return (0);
}
