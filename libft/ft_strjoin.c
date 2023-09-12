/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:32:02 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/16 05:14:54 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// joins two strings together inside a malloc'd string.

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = malloc(s1len + s2len + 1);
	if (!res)
		return (NULL);
	res[s1len + s2len] = '\0';
	while (s2len-- > 0)
		res[s1len + s2len] = s2[s2len];
	while (s1len-- > 0)
		res[s1len] = s1[s1len];
	return (res);
}

char	*ft_strjoin_heap(char const *s1, char const *s2, t_stackheap *stack)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (str == NULL)
		return (NULL);
	if (heap_push(stack, str, free) == -1)
		return (NULL);
	return (str);
}
