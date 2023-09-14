/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 21:08:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

void	*ft_editenv(char *key, char *value, t_envp *env)
{
	size_t	i;
	size_t	key_len;
	int		isfind;
	char	*keys;
	char	*new_str;

	i = 0;
	isfind = 0;
	key_len = ft_strlen(key);
	keys = ft_strjoin(key, "=");
	if (keys == NULL)
		return (NULL);
	new_str = ft_strjoin(keys, value);
	if (new_str == NULL)
		return (NULL);
	while (i < env->len && !isfind)
	{
		if (ft_strncmp(key, env->env[i], key_len) == 0)
		{
			free(env->env[i]);
			env->env[i] = new_str;
			isfind = 1;
		}
		i++;
	}
	if (isfind == 0)
		free(new_str);
	return (env->env);
}