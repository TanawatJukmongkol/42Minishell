
#include "libminishell.h"

void	lexer(t_token_stream *output, char *src)
{
	t_token_stream	stage1;
	t_token_stream	stage2;
	t_token_stream	stage3;
	t_token_stream	stage4;

	stage1.begin = NULL;
	stage2.begin = NULL;
	stage3.begin = NULL;
	stage4.begin = NULL;
	stage1_tokenizer(&stage2, &stage1, src);
	stage2_tokenizer(&stage3, &stage2);
	stage3_tokenizer(&stage4, &stage3);
	stage4_tokenizer(output, &stage4);
}

