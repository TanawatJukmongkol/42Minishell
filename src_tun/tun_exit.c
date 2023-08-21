/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/21 23:16:58 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	tun_exit(t_stackheap *mem, int isexe)
{
	if (errno == ENOENT)
		ft_exit(mem, 127);
	if (errno == EACCES)
	{
		if (isexe != -1)
			ft_exit(mem, 126);
		ft_exit(mem, 1);
	}
	ft_exit(mem, 0);
}