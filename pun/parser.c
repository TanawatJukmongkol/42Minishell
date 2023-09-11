
#include "libminishell.h"

void	rearrange_token_heredoc(t_token_stream *s, t_token *t)
{
	if (t->type	!= __here_doc && t->next && t->next->type != __here_doc)
	{
		ft_token(s, t->type)->value = ft_strdup(t->value);
		return ;
	}
	if (t->next->type == __here_doc)
	{
		ft_token(s, __here_doc)->value = ft_strdup(t->next->next->value);
	}
	else
		ft_token(s, t->type)->value = ft_strdup(t->value);
}

void	parser(t_token_stream *output, t_token_stream *input)
{
	//t_token_stream	stage1;
	//t_token_stream	stage2;

	// stage1.begin = NULL;
	//stage2.begin = NULL;
	ft_token_consume(output, input, rearrange_token_heredoc);
	// ft_token_consume(output, stage2, );
}

