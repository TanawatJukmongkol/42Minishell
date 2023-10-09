/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:02:21 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/08 17:21:01 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_getcwd()
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	return (ft_strdup(cwd));
}
