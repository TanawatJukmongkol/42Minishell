/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/13 06:28:58 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_realpath(char *re_path, char **envp)
{
	(void)(re_path);
	(void)(envp);
	// replace first char ~ with $HOME

	// if (re_path[0] == '~')
		//
	// replace $VAR with value of $VAR
	// replace ~user with $HOME of user

	// replace . with current directory
	// replace .. with parent directory
	// replace // with /
	// replace /// with /

	// replace /./ with /
	// replace /../ with / (and remove parent directory)
	return (NULL);
}