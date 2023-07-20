/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/07/16 11:39:36 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_chdir(char *path)
{
	(void)(path);
	// if path is NULL, cd to $HOME
	// if path is -, change to $OLDPWD
	// if path is ~, change to $HOME
	// if path is ~user, change to $HOME of user
	// if path is ., do nothing
	// if path is .., change to parent directory
	// if path is /, change to root directory
	// if path is //, change to root directory
	// if path is ///, change to root directory
	return (0);
}
