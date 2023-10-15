/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:06:46 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/15 23:40:10 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static int	sb_run_editor(char *key, char *new_str, t_envp *env)
{
	size_t	i;
	size_t	key_len;
	int		isfind;

	i = 0;
	key_len = ft_strlen(key);
	isfind = 0;
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
	return (isfind);
}

void	*ft_editenv(char *key, char *value, t_envp *env)
{
	char	*keys;
	char	*new_str;

	keys = ft_strjoin(key, "=");
	if (keys == NULL)
		return (NULL);
	new_str = ft_strjoin(keys, value);
	free(keys);
	if (new_str == NULL)
		return (NULL);
	if (sb_run_editor(key, new_str, env) == 0)
		free(new_str);
	return (env->env);
}
