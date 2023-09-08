/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/08 17:53:37 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Thrown Everything that need in linux here
# ifdef __linux
#  ifndef OPEN_MAX
#   define OPEN_MAX 10420
#  endif
# endif

/** Token stream **/

/* token type enum */
typedef enum	e_token_type
{
	// Not defined
	__none,
	// Pipes
	__pipe,
	// C standard out file operations
	__redirr_in,
	__here_doc,
	__redirr_trunc,
	__redirr_append,
	// cmd & argv
	__cmd,
	__argv
}				t_token_type;

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

/** main **/
typedef struct s_main
{
	char			*_path;
	t_envp			*_envp;
	t_token_stream	*_token;
	t_stackheap		*_mem;
	int				_ngong;
}				t_main;

/* misc */
char	*ft_readline(const char *prompt);
char	*ft_realpath(char *re_path, char **envp);
char	*ft_getcwd(void);
char	*ft_chdir(char *path);
char	*get_next_qoute(char *str, char *match, int single);
void	ft_exit(t_stackheap *mem ,int status);

/** env **/
void	ft_initenv(t_envp *_envp, char **envp);
void	ft_genenv(t_envp *envp);

/** token **/
t_token	*ft_token(t_token_stream *stream, t_token_type type);
void	ft_token_consume(t_token_stream *dst,
			t_token_stream *src, void (*fn)(t_token_stream *s, t_token *t));
void	ft_tokenfree(t_token_stream *s);

#endif
