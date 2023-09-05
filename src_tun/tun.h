/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/04 06:41:49 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "../src_share/libminishell.h"

typedef struct s_exec
{
	t_main	*info;
	int		*infile;
	int		*outfile;
	char	*delimeter;
	char	*cmd;
	char	**argv;
}				t_exec;

int		tun_builin_handler(char *cmd, char **av, t_main *info);

void	tun_exit(t_stackheap *mem, int isexe);

# endif