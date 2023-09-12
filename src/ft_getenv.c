/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:27 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/12 19:31:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*ft_getenv(t_envp *envp, char *key)
{
	size_t	i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (i < envp->len)
	{
		if (ft_strncmp(key, envp->env[i], key_len) == 0)
			return (ft_strchr(envp->env[i], '=') + 1);
		i++;
	}
	return (NULL);
}
