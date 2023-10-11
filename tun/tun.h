/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/12 01:59:47 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "../src/libminishell.h"
# include "../pun/pun.h"

# ifndef BUILTIN_PID
#  define BUILTIN_PID -69
# endif

typedef struct s_pipe
{
	int		**box;
	size_t	n;
}				t_pipe;

typedef struct s_exec
{
	t_main	*_info;
	t_pipe	_pipes;
	int		*infile;
	int		*outfile;
	int		in_len;
	int		out_len;
	char	**delimeter;
	char	**argv;
}				t_exec;

// ctrl-c = SIGINT
// ctrl-d = EOF-Signal (don't handle)
// ctrl-f = SIGQUIT

/*		tun_builtin		*/
int		tun_builin_handler(char *cmd, char **av, t_exec *exe);
int		tun_echo(char **av, t_exec *exe);
void	tun_builtin_exit(t_exec *info, char **av);

/*		tun_program_exit.c		*/
void	tun_parent_exit(int status, t_exec *exe, t_token_stream *box);
void	tun_clear_process(t_exec *exe);
void	tun_flush_subset(t_token_stream *subset);

/*		tun_init.c		*/
int		tun_init_exec_parent(t_exec *exe, t_main *info, size_t pipe_n);
int		tun_init_exec_child(t_exec *exe, t_token_stream *subset);
int		tun_init_box(t_token_stream subset, t_exec *exe);

/*		tun_split_token.c	*/
t_token_stream	*tun_split_token(t_main *info, size_t *pipe_n);
void			tun_free_token_box(t_token_stream *box, size_t pipe_n);

/*		tun_pipe.c		*/
int		tun_alloc_pipe(t_pipe *pipes, size_t n);
void	tun_close_pipe(t_pipe *pipes);

/*		tun_file.c		*/
int		tun_open(const char *path, int oflag, mode_t mode);
void	tun_close(int fd);
int		tun_dup2(int fd1, int fd2);
int		tun_pipe(int fdes[2]);
void	tun_close_files(int *fdes, int n);

/*		tun_fork.c		*/
int		tun_fork(void);
int		tun_waitpid(int pid, int *stat, int option);
int		tun_redirct(int *fdes, int len, int std, int isok);

/*		tun_translate	*/
void	tun_get_argv(t_token_stream subset, t_exec *exe);
int		tun_get_infile(t_token_stream subset, t_exec *exe);
int		tun_get_outfile(t_token_stream subset, t_exec *exe);

/*		tun_child.c		*/
void	tun_clean_child(t_exec *exe);
void	tun_child_process(t_token_stream *subset, t_exec *exe, size_t child_no);

/*		tun_parent.c	*/
void	tun_parent_process(t_main *info, t_token_stream *box, size_t pipe_n);

/*		tun_exeve.c		*/
void	tun_execve(t_exec *exe);

/*		tun_heredoc.c	*/
int		tun_heredoc(t_exec *exe);

# endif
