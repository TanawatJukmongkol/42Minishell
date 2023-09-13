/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/14 03:48:03 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

static char	*join_path(char *dst, char *path)
{
	char	*join;

	join = ft_strjoin("/", path);
	free(path);
	if (!dst)
		return (join);
	path = ft_strjoin(dst, join);
	free(dst);
	free(join);
	return (path);
}

static char	*remove_path(char *path)
{
	char	*tmp;

	tmp = ft_substr(path, 0, ft_strrchr(path, '/') - path);
	free(path);
	return (tmp);
}

static char	*remove_repath(char *path)
{
	char	*tmp;
	char	*stopper;

	stopper = ft_strchr(path + 1, '/');
	if (!stopper)
	{
		free(path);
		return (NULL);
	}
	tmp = ft_strdup(stopper + 1);
	free(path);
	path = ft_strtrim(tmp, "/");
	free(tmp);
	return (path);
}

static char	*get_repath(char *re_path, t_envp *envp, t_stackheap *mem)
{
	char	*tmp;
	char	*tmp2;

	if (ft_strncmp(re_path, "~/", 2) == 0)
	{
		tmp = ft_strdup(re_path + 1);
		free(re_path);
		re_path = ft_strjoin(ft_getenv(envp, "HOME"), tmp);
		free(tmp);
	}
	if (re_path[0] != '/')
	{
		tmp = ft_getcwd(mem);
		tmp2 = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = ft_strjoin(tmp2 + 1, re_path);
		free(tmp2);
	}
	else
		tmp = ft_strtrim(re_path, "/");
	free(re_path);
	return (tmp);
}

char	*ft_realpath(char *re_path, t_envp *env, t_stackheap *mem)
{
	char	*real;
	size_t	len;

	if (ft_strncmp(re_path, "~\0", 2) == 0)
	{
		free(re_path);
		return (ft_strdup_heap(ft_getenv(env, "HOME"), mem));
	}
	real = NULL;
	re_path = get_repath(re_path, env, mem);
	while (re_path)
	{
		if (!ft_strchr(re_path, '/'))
			len = ft_strlen(re_path);
		else
			len = ft_strchr(re_path, '/') - re_path;
		if (ft_strncmp(re_path, "../", 3) == 0)
			real = remove_path(real);
		else if (ft_strncmp(re_path, "./", 2))
			real = join_path(real, ft_substr(re_path, 0, len));
		re_path = remove_repath(re_path);
	}
	if (heap_push(mem, real, free) == -1)
		return (NULL);
	return (real);
}
