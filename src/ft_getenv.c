/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:27 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/11 01:54:08 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// FIX1

char	*ft_getenv(t_envp *envp, char *key)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	while (i < envp->len)
	{
		str_len = ft_strclen(envp->env[i], '=');
		if (ft_strncmp(key, envp->env[i], str_len) == 0)
			return (ft_strchr(envp->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
