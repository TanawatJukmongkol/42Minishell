/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/08 22:55:07 by Tanawat J.       ###   ########.fr       */
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
	char	*old;

	real = ft_realpath(path, NULL);
	if (!real)
		return (ENOMEM);
	if (!chdir(real))
		return (errno);
	// heap_free(&info->_mem, info->_path);
	info->_path = real;
	old = ft_getenv(&info->_envp, "PWD");
	if (old == NULL)
		old = "";
	if (ft_editenv("OLDPWD", old, &info->_envp) == NULL)
	{
		// heap_free(&info->_mem, info->_path);
		return (ENOMEM);
	}
	if (ft_editenv("PWD", real, &info->_envp) == NULL)
	{
		// heap_free(&info->_mem, info->_path);
		return (ENOMEM);
	}
	return (0);
}
