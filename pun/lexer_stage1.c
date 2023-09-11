
#include "libminishell.h"

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

void	stage1_tokenizer(t_token_stream *dst, t_token_stream *stage1, char *input)
{
	ft_token(stage1, __none)->value = input;
	ft_token_consume(dst, stage1, white_space);
}

