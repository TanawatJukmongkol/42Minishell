/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 03:39:14 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Universal Marco
# ifndef ERR_MSG
#  define ERR_MSG "minishell"
# endif

// Linux's Marco
# ifdef __linux
#  ifndef _POSIX_C_SOURCE
#   define _POSIX_C_SOURCE 200809L
#  endif
#  ifndef OPEN_MAX
#   define OPEN_MAX 10420
#  endif
# endif

typedef struct sigaction	t_sigaction;

/** Token stream **/

/* token type enum */
typedef enum e_token_type
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
typedef struct s_envp
{
	char		**env;
	size_t		len;
}				t_envp;

/** main **/
typedef struct s_main
{
	char			*_path;
	t_envp			_envp;
	t_token_stream	_token;
	t_stackheap		_mem;
	int				_ngong;
}				t_main;

/** main **/
int		ft_init_main(t_main *info);

/* misc */
char	*ft_readline(const char *prompt, t_stackheap *mem);
char	*ft_realpath(char *re_path, t_envp *env, t_stackheap *mem);
char	*ft_getcwd(t_stackheap *mem);
char	*ft_chdir(char *path, t_stackheap *mem);
char	*get_next_qoute(char *str, char *match, int single);
void	ft_exit(t_stackheap *mem ,int status);

/** env **/
char	**ft_initenv(t_envp *_envp, char **envp, t_stackheap *mem);
void	ft_clear_envp(void *env);
char	*ft_getenv(t_envp *envp, char *key);
void	*ft_setenv(char *member, t_envp *env, t_stackheap *mem);
void	*ft_unsetenv(char *key, t_envp *env, t_stackheap *mem);
void	*ft_editenv(char *member, t_envp *env);

/** signal **/
int	ft_sig_init(t_sigaction *s, int flag, void (*hand)(int),\
				void (*sact)(int, siginfo_t *, void *));

#endif
