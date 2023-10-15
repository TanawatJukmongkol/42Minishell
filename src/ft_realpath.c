/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/16 01:25:30 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"


char	*join_path(char *dst, char *src)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", src);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(dst, tmp);
	free(dst);
	free(tmp);
	return (tmp2);
}

int	init_begin_path(char *re_path, char **begin, char **path, t_main *m)
{
	if (!re_path || !*re_path)
		return (1);
	if (!ft_strncmp(re_path, "~", 2) || !ft_strncmp(re_path, "~/", 2))
		*begin = ft_strjoin(m->_home, re_path + 1);
	else if (re_path[0] == '/')
		*begin = ft_strdup(re_path);
	else
	{
		*begin = ft_getcwd();
		if (!*begin)
			return (1);
		*begin = join_path(*begin, re_path);
	}
	*path = ft_strdup("/");
	return (!*path || !*begin);
}

void	climb_path(char **trim, char **path)
{
	if (!ft_strncmp(*trim, "..", ft_strlen(*trim)))
	{
		*ft_strrchr(*path, '/') = '\0';
		if (!*path[0])
		{
			*path[0] = '/';
			*path[1] = '\0';
		}
	}
	else
	{
		if (!*path[1])
			*path[0] = '\0';
		*path = join_path(*path, *trim);
	}
}

void	free_begin(char *re_path, char **begin, char **trim)
{
	free(*begin);
	if (*trim)
		free(*trim);
	*begin = re_path;
}

char	*ft_realpath(char *re_path, t_main *m)
{
	char	*next_slash;
	char	*begin;
	char	*path;
	char	*trim;

	if (!*re_path || init_begin_path(re_path, &begin, &path, m))
		return (NULL);
	next_slash = begin;
	while (*re_path)
	{
		next_slash = ft_strchr(begin, '/');
		if (!next_slash)
			next_slash = re_path + ft_strlen(re_path);
		trim = ft_substr(begin, 0, next_slash - begin);
		if (!trim)
			return (NULL);
		if (*trim && ft_strncmp(trim, ".", ft_strlen(trim)))
			climb_path(&trim, &path);
		re_path = ft_strdup(next_slash + (*next_slash != 0));
		free_begin(re_path, &begin, &trim);
	}
	if (!re_path)
		return (NULL);
	free(re_path);
	return (path);
}
