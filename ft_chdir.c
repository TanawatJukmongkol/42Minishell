/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/19 02:50:09 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// if path is NULL, cd to $HOME -> no $HOME = bash: cd: HOME not set
// if path is -, change to $OLDPWD -> print $OLDPWD & no $OLDPWD = bash: cd: OLDPWD not set
// if path is ~, change to $HOME -> no $HOME mean nothing
// if path is ~user, change to $HOME of user
// if path is ., do nothing
// if path is .., change to parent directory
// if path is /, change to root directory
// if path is //, change to root directory
// if path is ///, change to root directory
// n-amount of / = single /

int	ft_chdir(char *path)
{
	(void)(path);
	
	return (0);
}
