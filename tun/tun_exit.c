/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tun_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/13 00:03:56 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

/*
0 : success
1: file permission denied
126: cmd permission denied
127: no such file or directory
*/

void	tun_child_exit(t_stackheap *mem, int isexe)
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

void	tun_builtin_exit(char **av, t_stackheap *mem)
{
	size_t	len;

	len = 0;
	while (av[len] != NULL)
		len++;
	if (len != 2)
		return ; // TODO : write perror here
	len = 0;
	while (av[1][len] != 0)
	{
		if (ft_isdigit(av[1][len]) == 0)
			return ; // TODO : write perror & exit
		len++;
	}
	ft_exit(mem, ft_atoi(av[1]));
}