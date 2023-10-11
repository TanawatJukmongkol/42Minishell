/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:12 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/11 01:03:48 by tponutha         ###   ########.fr       */
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

static void	*sb_set_newenv(t_envp *env, char ***new_env, char *member)
{
	(*new_env)[env->len - 1] = ft_strdup(member);
	if ((*new_env)[env->len - 1] == NULL)
	{
		free(env->env);
		ft_clear_envp(*new_env);
		*new_env = NULL;
		return (NULL);
	}
	free(env->env);
	env->env = *new_env;
	env->env[env->len] = NULL;
	return (*new_env);
}

// TODO : handle SHLVL
// WORK

void	*ft_setenv(char *member, t_envp *env)
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
	while (i < env->len - 1)
	{
		new_env[i] = env->env[i];
		i++;
	}
	return (sb_set_newenv(env, &new_env, member));
}