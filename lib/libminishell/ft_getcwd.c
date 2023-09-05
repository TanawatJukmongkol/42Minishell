/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:02:21 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/23 16:03:09 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_getcwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
		return (NULL);
	return (ft_strdup(cwd));
}
