/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:54:51 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/11 04:05:13 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static char	*sb_find_key(t_envp *envp, char *key)
{
	size_t	i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (i < envp->len)
	{
		if (ft_strncmp(key, envp->env[i], key_len) == 0)
			return (envp->env[i]);
		i++;
	}
	return (NULL);
}

void	*ft_unsetenv(char *key, t_envp *env, t_stackheap *mem)
{
	size_t	i;
	char	*val;
	char	**new_env;

	i = 0;
	val = sb_find_key(env, key);
	if (val == NULL)
		return (env->env);
	env->len--;
	new_env = malloc(sizeof(char *) * (env->len + 1));
	if (new_env == NULL)
		return (NULL);
	heap_discard(mem, env->env);
	heap_discard(mem, key);
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
