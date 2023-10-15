/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:54:51 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/16 01:38:26 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// TODO : handle SHLVL

char	*init_value(char *key, t_envp *env, size_t *i, size_t *j)
{
	char	*val;

	*i = 0;
	*j = 0;
	val = ft_getenv(env, key);
	if (val == NULL)
		return (NULL);
	val = val - 1 - ft_strlen(key);
	env->len--;
	return (val);
}

void	*ft_unsetenv(char *key, t_envp *env)
{
	size_t	i;
	size_t	j;
	char	*val;
	char	**new_env;

	val = init_value(key, env, &i, &j);
	if (!val)
		return (env->env);
	new_env = malloc(sizeof(char *) * (env->len + 1));
	if (new_env == NULL)
		return (NULL);
	while (i < env->len + 1)
	{
		if (env->env[i] != val)
			new_env[j++] = env->env[i];
		else
			free(env->env[i]);
		i++;
	}
	free(env->env);
	env->env = new_env;
	env->env[env->len] = NULL;
	return (new_env);
}
