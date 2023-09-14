/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 21:03:54 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

/*
0 = success
ENOMEM = malloc fail
ELSE = can't access or don't exist
*/

int	ft_chdir(char *path, t_main *info)
{
	char	*real;

	real = ft_realpath(path, NULL, &info->_mem);
	if (!real)
		return (ENOMEM);
	if (!chdir(real))
		return (errno);
	
	return (0);
}
