/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/09 01:02:12 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"

char	*join_path(char *dst, char *src)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("/", src);
	// heap_free(m, src);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(dst, tmp);
	free(dst);
	free(tmp);
	return (tmp2);
}

char	*ft_realpath(char *re_path, t_main *m)
{
	char	*next_slash;
	char	*begin;
	char	*path;
	char	*trim;

	if (!re_path || !*re_path)
		return (NULL);
	if (!ft_strncmp(re_path, "~", 2) || !ft_strncmp(re_path, "~/", 2))
		begin = ft_strjoin(m->_home, re_path + 1);
	else if (re_path[0] == '/')
		begin = ft_strdup(re_path);
	else
	{
		begin = ft_strdup(getenv("PWD")); // TODO : if PWD doesn't exist, then SEGFAULT
		if (!begin)
			return (NULL);
		begin = join_path(begin, re_path);
	}
	if (!begin)
		return (NULL);
	path = ft_strdup("/");
	if (!path)
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
		{
			if (!ft_strncmp(trim, "..", ft_strlen(trim)))
			{
				*ft_strrchr(path, '/') = '\0';
				if (!path[0])
				{
					path[0] = '/';
					path[1] = '\0';
				}
			}
			else
			{
				if (!path[1])
					path[0] = '\0';
				path = join_path(path, trim);
			}
		}
		re_path = ft_strdup(next_slash + (*next_slash != 0));
		free(begin);
		if (trim)
			free(trim);
		begin = re_path;
	}
	if (!re_path)
		return (NULL);
	free(re_path);
	return (path);
}


/*void	build_path(t_token_stream *s, t_token *t, void *vars)
{
	(void)(s);
	printf("%s\n", t->value);
	(void)(vars);
}

void	split_slash(t_token_stream *s, t_token *t, void *vars)
{
	char	*ptr;
	char	*next_match;
	size_t	len;

	(void)(vars);
	ptr = t->value;
	next_match = ptr;
	while (1)
	{
		next_match = ft_strchr(next_match, '/');
		if (!next_match)
			next_match = ptr + ft_strlen(ptr);
		len = next_match - ptr;
		if (len)
			ft_token(s, t->type)->value = ft_substr(ptr, 0, len);
		if (!*next_match)
			break ;
		ptr = ++next_match;
	}
}*/

/*char	*ft_realpath(char *re_path, t_main *m)
{
	t_token_stream	stream;
	t_token_stream	slash;
	t_token_stream	climb;
	t_token			*prev;
	t_token			*current;
	char			*res;

	(void)(m);
	res = NULL;
	stream.begin = NULL;
	slash.begin = NULL;
	climb.begin = NULL;
	ft_token(&stream, __none)->value = ft_strdup(re_path);
	ft_token_consume(&slash, &stream, split_slash, m);
	current = slash.begin;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->next->value, "..", ft_strlen(current->value)))
		{
			free(current->value);
			current->
			continue ;
		}
		if (!ft_strncmp(current->value, ".", ft_strlen(current->value))
			|| !ft_strncmp(current->value, "..", ft_strlen(current->value)))
		{
			free(current->value);
			current->value = NULL;
		}
		// printf("%s\n", current->value);
		prev = current;
		current = current->next;
	}
	while (slash.begin)
		ft_token_consume(&climb, &slash, build_path, m);
	return (res);
}*/

/*
int main(int ac, char **av, char **envp)
{
	t_main	m;

	(void)(ac);
	(void)(av);
	(void)(envp);
	if (ac < 2)
		return (printf("Don't forget to give an argument to the program, idiot!\n"), 0);
	heap_init(&m._mem);
	m._home = getenv("HOME");

	char *a = av[1];
	char *b = ft_realpath(a, &m);
	//ft_realpath(a, &m);
	printf("final: %s\n", b);
	heap_free(&m._mem, b);
	// heap_purge(&m._mem);
	return (0);
}
*/
