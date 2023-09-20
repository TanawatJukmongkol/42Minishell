/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:38:07 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/21 05:48:47 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libminishell.h"
// #include "../pun/pun.h"

/*static char	*join_path(char *dst, char *path)
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

	if (ft_strncmp(re_path, "~", 1) == 0)
		return (free(re_path), ft_strdup_heap(ft_getenv(env, "HOME"), mem));
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
}*/

/*char	*ft_strredup_heap(char *head, char *str, t_stackheap *mem)
{
	char	*ret;

	ret = ft_strdup_heap(str, mem);
	heap_free(mem, head);
	return (ret);
}*/

char	*join_path(char *dst, char *src, t_mem *m)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_heap("/", src, m);
	// heap_free(m, src);
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin_heap(dst, tmp, m);
	heap_free(m, dst);
	heap_free(m, tmp);
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
		begin = ft_strjoin_heap(m->_home, re_path + 1, &m->_mem);
	else if (re_path[0] == '/')
		begin = ft_strdup_heap(re_path, &m->_mem);
	else
	{
		begin = ft_strdup_heap(getenv("PWD"), &m->_mem);
		if (!begin)
			return (NULL);
		begin = join_path(begin, re_path, &m->_mem);
	}
	if (!begin)
		return (NULL);

	path = ft_strdup_heap("/", &m->_mem);
	if (!path)
		return (NULL);
	next_slash = begin;
	while (*re_path)
	{
		next_slash = ft_strchr(begin, '/');
		if (!next_slash)
			next_slash = re_path + ft_strlen(re_path);
		trim = ft_substr_heap(begin, 0, next_slash - begin, &m->_mem);
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
				path = join_path(path, trim, &m->_mem);
			}
		}
		re_path = ft_strdup_heap(next_slash + (*next_slash != 0), &m->_mem);
		heap_free(&m->_mem, begin);
		if (trim)
			heap_free(&m->_mem, trim);
		begin = re_path;
	}
	if (!re_path)
		return (NULL);
	heap_free(&m->_mem, re_path);
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
