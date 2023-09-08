/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/08 02:38:54 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

int	tun_init(t_exec *exe, t_main *info)
{
	exe->_info = info;
	tun_alloc_pipe(info, exe->_pipes, 0);
	exe->infile = NULL;
	exe->in_len = 0;
	exe->outfile = NULL;
	exe->out_len = 0;
	exe->delimeter = NULL;
	exe->argv = NULL;
}