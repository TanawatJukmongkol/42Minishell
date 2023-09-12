/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:44:47 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 05:53:23 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pun.h"

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

