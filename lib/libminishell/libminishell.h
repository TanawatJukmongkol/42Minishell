/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/20 18:01:01 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>

/** Token stream **/

/* token type enum */
enum e_token_type
{
	// Not defined
	__none,
	// Identifyer (variables, environment, etc)
	__iden,
	// Pipes
	__pipe,
	// C standard out file operations
	__redir_in,
	__here_doc,
	__redirr_override,
	__redirr_append
};
typedef enum e_token_type	t_token_type;

/* token node */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

/* token stream */
typedef struct s_token_stream
{
	t_token	*begin;
	t_token	*last;
}				t_token_stream;

/*
	Creates a new memory allocated token and then join to the token stream.
	returns the created node, and NULL on failure
*/
t_token			*ft_token(t_token_stream *stream, t_token_type type);

//	Consumes the token stream, with void (*fn)(t_token *t) as the iterator.
void			ft_token_consume(t_token_stream *dst, \
	t_token_stream *src, void (*fn)(t_token_stream *stream, t_token *t));

//	Pushes token to the stream.
void			ft_stream_join(t_token_stream *dst, t_token_stream *src);

#endif
