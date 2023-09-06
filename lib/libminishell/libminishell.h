/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/06 18:00:51 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>

# ifdef __linux
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

/** Token stream **/

/* token type enum */
enum e_token_type
{
	// Not defined
	__none,
	// Pipes
	__pipe,
	// C standard out file operations
	__redir_in,
	__here_doc,
	__redirr_override,
	__redirr_append,
	// cmd & argv
	__cmd,
	__argv
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

/** env **/
typedef struct s_envnode
{
	char				*key;
	char				*value;
	struct s_envnode	*next;
}				t_envnode;

typedef struct s_envp
{
	char		**cache;
	t_envnode	*begin;
	t_envnode	*last;
	size_t		len;
}				t_envp;

/* misc */
char	*ft_readline(const char *prompt);
char	*ft_realpath(char *re_path, char **envp);
char	*ft_getcwd(void);
char	*ft_chdir(char *path);

/** env **/
void	ft_initenv(t_envp *_envp, char **envp);
void	ft_genenv(t_envp *envp);

/** token **/
t_token	*ft_token(t_token_stream *stream, t_token_type type);
void	ft_token_consume(t_token_stream *dst,
			t_token_stream *src, void (*fn)(t_token_stream *s, t_token *t));
void	ft_tokenfree(t_token_stream *s);

#endif
