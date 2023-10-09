/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:54:51 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/08 22:52:45 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// TODO : handle SHLVL

void	*ft_unsetenv(char *key, t_envp *env)
{
	size_t	i;
	char	*val;
	char	**new_env;

	i = 0;
	val = ft_getenv(env, key);
	if (val == NULL)
		return (env->env);
	val = val - 1 - ft_strlen(key);
	env->len--;
	new_env = malloc(sizeof(char *) * (env->len + 1));
	if (new_env == NULL)
		return (NULL);
	// heap_discard(mem, env->env);
	// heap_discard(mem, key);
	while (i < env->len)
	{
		if (env->env[i] == val)
			continue ;
		new_env[i] = env->env[i];
		i++;
	}
	free(env->env);
	env->env = new_env;
	return (new_env);
}
