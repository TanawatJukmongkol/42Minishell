/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:02:21 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/11 02:25:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_getcwd(t_stackheap *mem)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	return (ft_strdup_heap(cwd, mem));
}
