/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/22 00:05:02 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUN_H
# define TUN_H
# include "../libminishell.h"

typedef struct	s_exec
{
	char			*current_path;
	t_envp			*env;
	t_token_stream	*stream;
	t_mem			*mem;
}	t_exec;

int		tun_builin_handler(char *cmd, char **av, t_exec *info);

void	tun_exit(t_stackheap *mem, int isexe);

# endif