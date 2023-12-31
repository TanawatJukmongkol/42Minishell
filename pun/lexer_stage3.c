/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage3_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:34 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 22:20:31 by tjukmong         ###   ########.fr       */
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

static void	replace_to_return(char **str, char **res, char **next_nonchar,
		t_main *m)
{
	char	*tmp;
	char	*nums;

	(*str)++;
	tmp = *res;
	nums = ft_itoa(m->_ngong);
	*res = ft_strjoin(tmp, nums);
	free(nums);
	free(tmp);
	*next_nonchar = *str;
	return ;
}

static void	replace_to_env(char **res, char **next_nonchar, char **next_match,
		t_main *m)
{
	char	*str;
	char	*env;
	char	*tmp;
	char	*get_env;

	str = (*next_match) + 1;
	if (*str == '?')
		return (replace_to_return(&str, res, next_nonchar, m));
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (str > (*next_match) + 1)
	{
		env = ft_substr(*next_match, 1, str - *next_match - 1);
		tmp = *res;
		get_env = ft_getenv(&m->_envp, env);
		if (get_env)
		{
			*res = ft_strjoin(tmp, get_env);
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

	(void)(vars);
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
			replace_to_env(&res, &next_nonchar, &next_match, vars);
		if (!*next_match)
			break ;
		next_match += next_nonchar - next_match;
		ptr = next_match;
	}
	ft_token(s, t->type)->value = res;
}

void	stage3_tokenizer(t_token_stream *dst, t_token_stream *stage3, t_main *m)
{
	while (stage3->begin)
		ft_token_consume(dst, stage3, env_replace, m);
}
