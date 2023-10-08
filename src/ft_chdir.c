/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/09 00:49:36 by tponutha         ###   ########.fr       */
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
	{
		free(real);
		return (errno);
	}
	old = ft_getenv(&info->_envp, "PWD");
	if (old == NULL)
		old = "";
	if (ft_editenv("OLDPWD", old, &info->_envp) == NULL)
		return (ENOMEM);
	if (ft_editenv("PWD", real, &info->_envp) == NULL)
		return (ENOMEM);
	free(real);
	return (0);
}
