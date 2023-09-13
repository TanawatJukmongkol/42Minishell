/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 03:30:19 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "../src/libminishell.h"

typedef struct s_pipe
{
	int		**box;
	size_t	n;
}				t_pipe;

typedef struct s_token_set
{
	t_token_stream	*token_set;
	size_t			n;
	t_stackheap		*mem;
}				t_token_set;

typedef struct s_exec
{
	t_main	*_info;
	t_pipe	*_pipes;
	int		*infile;
	int		*outfile;
	int		in_len;
	int		out_len;
	char	*delimeter;
	char	**argv;
	char	**envp;
}				t_exec;

// ctrl-c = SIGINT
// ctrl-d = EOF-Signal (don't handle)
// ctrl-f = SIGQUIT

/*		tun_builtin.c		*/
int		tun_builin_handler(char *cmd, char **av, t_main *info);

/*		tun_exit.c		*/
void	tun_child_exit(t_stackheap *mem, int isexe);
void	tun_builtin_exit(char **av, t_stackheap *mem);

/*		tun_init.c		*/
int		tun_init_exec_parent(t_exec *exe, t_main *info);
int		tun_init_exec_child(t_exec *exe, t_token_stream *subset);
t_exec	tun_exec_init(void);

/*		tun_split_token.c	*/
t_token_stream	*tun_split_token(t_main *info, size_t *pipe_n);
void			tun_free_token_box(void *tokens);

/*		tun_pipe.c		*/
int		tun_alloc_pipe(t_main *info, t_pipe *pipes, size_t n);
void	tun_close_pipe(t_main *info, t_pipe *pipes);

/*		tun_file.c		*/
int		tun_open(const char *path, int oflag, mode_t mode);
void	tun_close(int fd);
int		tun_dup2(int fd1, int fd2);
int		tun_pipe(int fdes[2]);

/*		tun_fork.c		*/
int		tun_fork(const char *msg);
int		tun_waitpid(int pid, int *stat, int option, const char *msg);

/*		tun_translate	*/
int		tun_count_type(t_token_stream *subset, t_token_type t1, t_token_type t2);
char	**tun_get_argv(t_token_stream *subset, t_main *info);
int		tun_get_infile(t_token_stream *subset, t_exec *exe);
int		tun_get_outfile(t_token_stream *subset, t_exec *exe);

/*		tun_child.c		*/
int		tun_redirct(int *fdes, int len, int std);
void	tun_clean_child(t_exec *exe);
void	tun_child_process(t_token_stream *subset, t_exec *exe, size_t child_no);

/*		tun_parent.c	*/
void	tun_parent_process(t_main *info);

# endif
