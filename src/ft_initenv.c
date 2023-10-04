/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:21 by tponutha          #+#    #+#             */
/*   Updated: 2023/10/04 20:44:59 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

// static void	*sb_failsafe(char **env)
// {
// 	size_t	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		free(env[i]);
// 		i++;
// 	}
// 	free(env);
// 	return (NULL);
// }

char	**ft_initenv(t_envp *_envp, char **envp, t_stackheap *mem)
{
	size_t	i;

	i = 0;
	_envp->len = 0;
	while (envp[_envp->len] != NULL)
		_envp->len++;
	_envp->env = malloc(sizeof(char *) * (_envp->len + 1));
	if (_envp->env == NULL)
		return (NULL);
	while (i < _envp->len)
	{
		_envp->env[i] = ft_strdup(envp[i]);
		if (_envp->env[i] == NULL)
			return (ft_clear_envp(_envp->env), NULL);
		i++;
	}
	(void)(mem);
	// if (heap_push(mem, _envp->env, ft_clear_envp) == -1)
	// 	return (NULL);
	return (_envp->env);
}

// void	ft_initenv(t_envp *_envp, char **envp)
// {
// 	_envp->len = 0;
// 	_envp->last = NULL;
// 	_envp->_env = NULL;
// 	if (!envp[0])
// 	{
// 		_envp->begin = NULL;
// 		return ;
// 	}
// 	_envp->begin = malloc(sizeof(t_envnode));
// 	_envp->last = _envp->begin;
// 	while (envp[_envp->len])
// 	{
// 		if (_envp->len)
// 		{
// 			_envp->last->next = malloc(sizeof(t_envnode));
// 			_envp->last = _envp->last->next;
// 		}
// 		_envp->last->key = ft_substr(envp[_envp->len], 0,
// 				ft_strchr(envp[_envp->len], '=') - envp[_envp->len]);
// 		_envp->last->value = ft_substr(envp[_envp->len],
// 				ft_strchr(envp[_envp->len], '=') - envp[_envp->len] + 1,
// 				ft_strlen(envp[_envp->len]));
// 		_envp->last->next = NULL;
// 		_envp->len++;
// 	}
// }
