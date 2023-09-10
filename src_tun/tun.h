/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/09 19:20:31 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "../libminishell/libminishell.h"

typedef struct s_pipe
{
	int		**box;
	size_t	n;
}				t_pipe;

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

int		tun_builin_handler(char *cmd, char **av, t_main *info);

void	tun_exit(t_stackheap *mem, int isexe);

int		tun_init(t_exec *exe, t_main *info);

int		tun_alloc_pipe(t_main *info, t_pipe *pipes, size_t n);
void	tun_close_pipe(t_main *info, t_pipe *pipes);

int		tun_open(const char *path, int oflag, mode_t mode);
void	tun_close(int fd);
int		tun_dup2(int fd1, int fd2);
int		tun_pipe(int fdes[2]);

# endif