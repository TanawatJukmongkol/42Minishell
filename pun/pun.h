/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 06:30:37 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUN_H
# define PUN_H
# include "../src/libminishell.h"

typedef struct s_cmd_table
{
	char	*cmd;
	char	*here_doc;
	char	*infile;
	char	*outfile;
	int		trunc;
	int		search_argv;
	size_t	indx;
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
void	parser(t_token_stream *output, t_token_stream *input);

#endif

