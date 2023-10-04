/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/30 18:09:27 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

int		ft_init_main(t_main *info, char **envp)
{
	char	*ptr_home;

	heap_init(&info->_mem);
	info->_token.begin = NULL;
	info->_token.last = NULL;
	info->_ngong = 0;
	if (ft_initenv(&info->_envp, envp, &info->_mem) == NULL)
		return (-1);
	ptr_home = ft_getenv(&info->_envp, "HOME");
	if (ptr_home == NULL)
		ptr_home = "";
	info->_home = ft_strdup_heap(ptr_home, &info->_mem);
	if (info->_home == NULL)
		return (-1);
	info->_path = ft_getcwd(&info->_mem);
	if (info->_path == NULL)
		return (-1);
	return (0);
}