/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:54:51 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/12 14:05:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// TODO : handle SHLVL

void	*ft_unsetenv(char *key, t_envp *env)
{
	size_t	i;
	size_t	j;
	char	*val;
	char	**new_env;

	i = 0;
	j = 0;
	val = ft_getenv(env, key);
	if (val == NULL)
		return (env->env);
	val = val - 1 - ft_strlen(key);
	env->len--;
	new_env = malloc(sizeof(char *) * (env->len + 1));
	if (new_env == NULL)
		return (NULL);
	while (i < env->len + 1)
	{
		if (env->env[i] != val)
		{
			new_env[j] = env->env[i];
			j++;
		}
		else
			free(env->env[i]);
		i++;
	}
	free(env->env);
	env->env = new_env;
	env->env[env->len] = NULL;
	return (new_env);
}
