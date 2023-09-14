/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:12 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/14 18:35:08 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static void	*sb_editenv(char *member, char *p, t_envp *env)
{
	size_t	i;
	char	*new_str;

	i = 0;
	p = p - 1 - ft_strlen(member);
	new_str = ft_strdup(member);
	if (new_str == NULL)
		return (NULL);
	while (i < env->len)
	{
		if (p == env->env[i])
		{
			free(env->env[i]);
			env->env[i] = new_str;
			break ;
		}
		i++;
	}
	return (env->env);
}

void	*ft_setenv(char *member, t_envp *env, t_stackheap *mem)
{
	size_t	i;
	char	*find;
	char	**new_env;

	if (ft_strchr(member, '=') == NULL)
		return (env->env);
	find = ft_getenv(env, member);
	if (find != NULL)
		return (sb_editenv(member, find, env));
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