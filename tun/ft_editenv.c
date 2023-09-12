/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 21:25:16 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tun.h"

void	*ft_editenv(char *member, t_envp *env, t_stackheap *mem)
{
	size_t	i;
	size_t	key_len;
	char	*new_str;

	i = 0;
	key_len = ft_strlen(member);
	new_str = ft_strdup(member);
	if (new_str == NULL)
		return (NULL);
	while (i < env->len)
	{
		if (ft_strncmp(member, env->env[i], key_len) == 0)
		{
			free(env->env[i]);
			env->env[i] = new_str;
			break ;
		}
		i++;
	}
	return (env->env);
}