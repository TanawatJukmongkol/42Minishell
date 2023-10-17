/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage3_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:34 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 18:29:22 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

static char	*str_rejoin(char *dst, char *src)
{
	char	*tmp;

	tmp = ft_strjoin(dst, src);
	free(dst);
	free(src);
	return (tmp);
}

static void	replace_to_env(char **res, t_envp *envp,
	char **next_nonchar, char **next_match)
{
	char	*str;
	char	*env;
	char	*tmp;

	str = (*next_match) + 1;
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (str > (*next_match) + 1)
	{
		env = ft_substr(*next_match, 1, str - *next_match - 1);
		tmp = *res;
		if (ft_getenv(envp, env))
		{
			*res = ft_strjoin(tmp, ft_getenv(envp, env));
			free(tmp);
		}
		free(env);
	}
	else
		*res = str_rejoin(*res, ft_strdup("$"));
	*next_nonchar = str;
}

void	env_replace(t_token_stream *s, t_token *t, void *vars)
{
	char	*ptr;
	char	*next_match;
	char	*next_nonchar;
	char	*res;
	size_t	len;

	ptr = t->value;
	next_match = ptr;
	res = ft_strdup("");
	while (1)
	{
		next_match = get_next_qoute(next_match, "$", 2);
		len = next_match - ptr;
		if (len)
			res = str_rejoin(res, ft_substr(ptr, 0, len));
		if (*next_match)
			replace_to_env(&res, vars, &next_nonchar, &next_match);
		if (!*next_match)
			break ;
		next_match += next_nonchar - next_match;
		ptr = next_match;
	}
	ft_token(s, t->type)->value = res;
}

void	stage3_tokenizer(t_token_stream *dst, t_token_stream *stage3, t_main *m)
{
	t_token_stream	tmp;

	tmp.begin = NULL;
	while (stage3->begin)
		ft_token_consume(&tmp, stage3, return_replace, m);
	while (tmp.begin)
		ft_token_consume(dst, &tmp, env_replace, &m->_envp);
}
