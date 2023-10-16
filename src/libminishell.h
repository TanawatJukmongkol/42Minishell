/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 22:36:14 by tjukmong         ###   ########.fr       */
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
# include <string.h>

// Universal Marco
# ifndef ERR_MSG
#  define ERR_MSG "minishell"
# endif

// Linux's Marco / include
# ifdef __linux
#  include <readline/readline.h>
#  include <readline/history.h>
#  ifndef _POSIX_C_SOURCE
#   define _POSIX_C_SOURCE 200809L
#  endif
#  ifndef OPEN_MAX
#   define OPEN_MAX 10420
#  endif
# else
#  include "/usr/local/Cellar/readline/8.2.1/include/readline/readline.h"
#  include "/usr/local/Cellar/readline/8.2.1/include/readline/history.h"
# endif

typedef struct sigaction	t_sigaction;

/** Token stream **/

/* token type enum */
typedef enum e_token_type
{
	__none,
	__pipe,
	__redirr_in,
	__here_doc,
	__redirr_trunc,
	__redirr_append,
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
	char			*_home;
	t_envp			_envp;
	t_token_stream	_token;
	int				_ngong;
}				t_main;

/** main **/
int		ft_init_main(t_main *info, char **envp);
int		ft_clear_main(t_main *info, int status);

/* misc */
char	*ft_readline(const char *prompt);
char	*ft_realpath(char *re_path, t_main *m);
char	*ft_getcwd(void);
int		ft_chdir(char *path, t_main *info);
char	*get_next_qoute(char *str, char *match, int single);
void	ft_exit(t_main *info, int status);

/** env **/
char	**ft_initenv(t_envp *_envp, char **envp);
void	ft_clear_envp(char **envs);
char	*ft_getenv(t_envp *envp, char *key);
void	*ft_setenv(char *member, t_envp *env);
void	*ft_unsetenv(char *key, t_envp *env);
void	*ft_editenv(char *key, char *value, t_envp *env);

/** token **/
void	ft_tokenfree(t_token_stream *s);

/** signal **/
int		ft_sig_init(t_sigaction *s, int flag, void (*hand)(int), \
				void (*sact)(int, siginfo_t *, void *));
int		ft_signal(void);

#endif
