/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:27 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/17 22:02:54 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// FIX1

char	*ft_getenv(t_envp *envp, char *key)
{
	size_t	i;
	size_t	str_len;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (i < envp->len)
	{
		str_len = ft_strclen(envp->env[i], '=');
		if (key_len > str_len)
			str_len = key_len;
		if (ft_strncmp(key, envp->env[i], str_len) == 0)
			return (ft_strchr(envp->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
