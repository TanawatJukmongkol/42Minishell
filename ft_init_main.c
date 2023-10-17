/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/15 23:42:54 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int	ft_init_main(t_main *info, char **envp)
{
	char	*ptr_home;

	info->_token.begin = NULL;
	info->_token.last = NULL;
	info->_ngong = 0;
	if (ft_initenv(&info->_envp, envp) == NULL)
		return (-1);
	ptr_home = ft_getenv(&info->_envp, "HOME");
	if (ptr_home == NULL)
		ptr_home = "";
	info->_home = ft_strdup(ptr_home);
	if (info->_home == NULL)
		return (-1);
	return (0);
}
