/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_genenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:55:36 by tponutha          #+#    #+#             */
/*   Updated: 2023/09/10 02:25:27 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	ft_clear_envp(void *env)
{
	size_t	i;
	char	**envs;

	i = 0;
	envs = (char **)env;
	if (envs == NULL)
		return ;
	while (envs[i] != NULL)
	{
		free(envs[i]);
		i++;
	}
	free(envs);
}

// void	ft_genenv(t_envp *envp, t_stackheap *mem)
// {
// 	size_t		indx;

// 	ft_clear_envp(envp->env);
// 	envp->env = malloc(sizeof(char *) * (envp->len + 1));
// 	if (envp->env == NULL)
		
// 	envp->cache[envp->len] = NULL;
// 	tmp = envp->begin;
// 	indx = 0;
// 	while (tmp)
// 	{
// 		// val = ft_strjoin("=", tmp->value);
// 		envp->cache[indx] = ft_strjoin(tmp->key, tmp->value);
// 		// free(val);
// 		indx++;
// 		tmp = tmp->next;
// 	}
// }
//