/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_stage3_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:34 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/17 19:28:35 by tjukmong         ###   ########.fr       */
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

static void	replace_to_return(char **res, t_main *m,
	char **next_nonchar, char **next_match)
{
	char	*str;
	char	*tmp;
	char	*nums;

	str = (*next_match) + 2;
	tmp = *res;
	nums = ft_itoa(m->_ngong);
	*res = ft_strjoin(tmp, nums);
	free(nums);
	free(tmp);
	*next_nonchar = str;
}

void	return_replace(t_token_stream *s, t_token *t, void *vars)
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
		next_match = get_next_qoute(next_match, "$?", 2);
		len = next_match - ptr;
		if (len)
			res = str_rejoin(res, ft_substr(ptr, 0, len));
		if (*next_match)
			replace_to_return(&res, vars, &next_nonchar, &next_match);
		if (!*next_match)
			break ;
		next_match += next_nonchar - next_match;
		ptr = next_match;
	}
	ft_token(s, t->type)->value = res;
}
