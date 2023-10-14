/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/14 21:54:46 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUN_H
# define PUN_H
# include "../src/libminishell.h"

typedef struct s_cmd_table
{
	char			*cmd;
	int				search_argv;
	t_token_stream	infile;
	t_token_stream	outfile;
	t_token_stream	argv;
}				t_cmd_table;

/** token **/
t_token	*ft_token(t_token_stream *stream, t_token_type type);
void	ft_token_consume(t_token_stream *dst, t_token_stream *src,
			void (*fn)(t_token_stream *s, t_token *t, void *vars), void *vars);
void	ft_tokenfree(t_token_stream *s);

/** Lexer **/
void	lexer(t_token_stream *output, char *src);

// Stage 1
void	white_space(t_token_stream *s, t_token *t, void *vars);
void	stage1_tokenizer(t_token_stream *dst,
			t_token_stream *stage1, char *input);

// Stage 2-1
void	meta_heredoc(t_token_stream *s, t_token *t, void *vars);
void	meta_redirr_out_append(t_token_stream *s, t_token *t, void *vars);

// Stage 2-2
void	meta_pipe(t_token_stream *s, t_token *t, void *vars);
void	meta_redirr_in(t_token_stream *s, t_token *t, void *vars);
void	meta_redirr_out_trunc(t_token_stream *s, t_token *t, void *vars);
void	stage2_tokenizer(t_token_stream *dst, t_token_stream *stage2);

// Stage 3
void	env_replace(t_token_stream *s, t_token *t, void *vars);
void	stage3_tokenizer(t_token_stream *dst, t_token_stream *stage3);

// Stage 4
void	quote_remove(t_token_stream *s, t_token *t, void *vars);
void	stage4_tokenizer(t_token_stream *dst, t_token_stream *stage4);

// Parser
void	init_table(t_cmd_table *table);
void	rm_next(t_token *t);
void	append_table(t_token_stream *dst, t_token_stream *src);
void	purge_table(t_cmd_table *table);
void	parser(t_token_stream *output, t_token_stream *input);

#endif
