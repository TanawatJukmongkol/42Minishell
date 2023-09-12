/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:46:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/12 17:46:08 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	ft_initenv(t_envp *_envp, char **envp)
{
	_envp->len = 0;
	_envp->last = NULL;
	_envp->cache = NULL;
	if (!envp[0])
	{
		_envp->begin = NULL;
		return ;
	}
	_envp->begin = malloc(sizeof(t_envnode));
	_envp->last = _envp->begin;
	while (envp[_envp->len])
	{
		if (_envp->len)
		{
			_envp->last->next = malloc(sizeof(t_envnode));
			_envp->last = _envp->last->next;
		}
		_envp->last->key = ft_substr(envp[_envp->len], 0,
				ft_strchr(envp[_envp->len], '=') - envp[_envp->len]);
		_envp->last->value = ft_substr(envp[_envp->len],
				ft_strchr(envp[_envp->len], '=') - envp[_envp->len] + 1,
				ft_strlen(envp[_envp->len]));
		_envp->last->next = NULL;
		_envp->len++;
	}
}
