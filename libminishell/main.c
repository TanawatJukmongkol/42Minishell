/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/08 11:20:58 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"
#include <stdlib.h>

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

int	ft_isenv(int c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	env_replace(t_token_stream *s, t_token *t)
{
	char	*ptr;
	char	*next_match;
	char	*next_nonchar;
	char	*tmp;
	char	*tmp2;
	char	*res;
	char	*env;
	size_t	len;

	(void)(s);
	ptr = t->value;
	next_match = ptr;
	res = ft_strdup("");
	while (1)
	{
		next_match = get_next_qoute(next_match, "$", 0);
		len = next_match - ptr;
		if (len)
		{
			tmp = res;
			tmp2 = ft_substr(ptr, 0, len);
			res = ft_strjoin(tmp, tmp2);
			free(tmp2);
			free(tmp);
		}
		if (*next_match)
		{
			next_nonchar = next_match + 1;
			while (*next_nonchar && ft_isenv(*next_nonchar))
				next_nonchar++;
			if (next_nonchar > next_match + 1)
			{
				env = ft_substr(next_match, 1, next_nonchar - next_match - 1);
				tmp = res;
				if (getenv(env))
				{
					res = ft_strjoin(tmp, getenv(env));
					free(tmp);
				}
				free(env);
			}
			else
			{
				tmp = res;
				res = ft_strjoin(tmp, "$");
			}
		}
		if (!*next_match)
			break ;
		next_match += next_nonchar - next_match;
		ptr = next_match;
	}
	ft_token(s, t->type)->value = res;
}

void	stage3_tokenizer(t_token_stream *dst, t_token_stream *stage3)
{
	while(stage3->begin)
		ft_token_consume(dst, stage3, env_replace);
}

void	quote_remove(t_token_stream *s, t_token *t)
{
	int		q;
	int		dbq;
	char	*res;
	size_t	indx;
	size_t	indx_res;

	q = 0;
	dbq = 0;
	indx = 0;
	indx_res = 0;
	res = ft_calloc(ft_strlen(t->value) + 1, 1);
	while (t->value[indx])
	{
		if (!q && t->value[indx] == '\"')
			dbq = !dbq;
		else if (!dbq && t->value[indx] == '\'')
			q = !q;
		else
			res[indx_res++] = t->value[indx];
		indx++;
	}
	ft_token(s, t->type) -> value = res;
}

void	stage4_tokenizer(t_token_stream *dst, t_token_stream *stage4)
{
	while(stage4->begin)
		ft_token_consume(dst, stage4, quote_remove);
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
	t_token_stream	stage3;
	t_token_stream	stage4;
	t_token_stream	output;

	stage1.begin = NULL;
	stage2.begin = NULL;
	stage3.begin = NULL;
	stage4.begin = NULL;
	char	*cwd = ft_getcwd();
	prompt = ft_strjoin(cwd, "> ");
	free(cwd);
	line = ft_readline(prompt);
	free(prompt);
	if (!prompt)
		return (0);
	ft_token(&stage1, __none)->value = line;
	ft_token_consume(&stage2, &stage1, white_space); // Split space
	stage2_tokenizer(&stage3, &stage2); // Split Metachar
	stage3_tokenizer(&stage4, &stage3); // Replace $ENV
	stage4_tokenizer(&output, &stage4); // Remove quotes

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
