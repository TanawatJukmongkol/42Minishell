/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:12 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/11 03:21:42 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	*ft_setenv(char *member, t_envp *env, t_stackheap *mem)
{
	size_t	i;
	char	**new_env;

	i = 0;
	env->len++;
	new_env = malloc(sizeof(char *) * (env->len + 1));
	if (new_env == NULL)
		return (NULL);
	heap_discard(mem, env->env);
	heap_discard(mem, member);
	while (i < env->len - 1)
	{
		new_env[i] = env->env[i];
		i++;
	}
	new_env[env->len - 1] = member;
	free(env->env);
	env->env = new_env;
	return (new_env);
}