/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/18 04:35:25 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "libminishell.h"
# include "pun.h"

typedef struct s_pipe
{
	int		**box;
	size_t	n;
}				t_pipe;

typedef struct s_exec
{
	t_main	*_info;
	t_pipe	_pipes;
	t_pipe	_heredoc;
	int		*infile;
	int		*outfile;
	int		in_len;
	int		out_len;
	char	**argv;
}				t_exec;

typedef t_token_stream	t_tks;

// ctrl-c = SIGINT
// ctrl-d = EOF-Signal (don't handle)
// ctrl-f = SIGQUIT

/*		tun_builtin.c			*/
int		tun_isbuiltin(char *cmd);
int		tun_builtin_parent(t_token_stream *box, pid_t *pid, \
							t_exec *exe, size_t n);
int		tun_builtin_child(t_exec *exe);

/*		tun_builtin_additional	*/
void	tun_builtin_exit(t_token_stream *box, pid_t *pid, \
							t_exec *exe, size_t n);
int		tun_echo(char **av, t_exec *exe);
int		tun_cd(char **av, t_main *info);
int		tun_pwd(void);
int		tun_env(char **argv, t_envp *env);

/*		tun_program_exit.c		*/
void	tun_process_exit(int status, t_exec *exe, \
						t_token_stream *box, size_t n);
void	tun_clear_process(t_exec *exe);

/*		tun_init.c		*/
int		tun_init_exec_parent(t_exec *exe, t_main *info, size_t pipe_n);
int		tun_init_box(t_token_stream subset, t_exec *exe);

/*		tun_split_token.c	*/
t_tks	*tun_split_token(t_main *info, size_t *pipe_n);
void	tun_free_token_box(t_token_stream *box, size_t pipe_n);

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
int		tun_waitpid(pid_t pid, int *stat, int option);

/*		tun_translate.c	*/
int		tun_get_argv(t_token_stream subset, t_exec *exe);
int		tun_get_infile(t_token_stream subset, t_exec *exe);
int		tun_get_outfile(t_token_stream subset, t_exec *exe);

/*		tun_child.c		*/
void	tun_child_process(t_exec *exe, t_token_stream *box, \
							pid_t *pid, size_t i);
int		tun_redirct(int *fdes, int len, int std, int isok);

/*		tun_parent.c	*/
void	tun_parent_process(t_main *info, t_token_stream *box, size_t pipe_n);

/*		tun_exeve.c		*/
void	tun_execve(t_exec *exe, int e);

/*		tun_heredoc.c	*/
int		tun_heredoc(t_token_stream *box, size_t pipe_n, t_exec *exe);
int		tun_delimeter(char *del, char *line, size_t del_len, size_t len);
char	*tun_last_delimeter(t_token_stream subset);
int		tun_dup_heredoc(int fd1, int fd2);

/*		tun_perror.c	*/
void	tun_cmd_perror(t_exec *exe, char *err);
void	tun_file_perror(const char *msg, const char *path);

#endif
