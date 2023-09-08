/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:32:00 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/16 05:11:33 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Finds the substring of *s. Returns the pointer to malloc'd string,
// with the content of *s, starting from start, and end at pointer
// start + len
//
//Ex: 1| char *str = ft_substr("Hello, world!", 5, 4);
//	  2| printf("\"%s\"", str); // prints: "o, w"
//	  3| free(str);

// 1)	"Hello, world!"
// 		~~~~~^			s + start
// 2)	"Hello, world!"
// 			 ~~~^		write "o, w" to res (see ft_strlcpy.c).

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*res;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len >= s_len - start)
		len = s_len - start;
	if (start > s_len)
	{
		start = s_len;
		len = 0;
	}
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

char	*ft_substr_heap(const char *s, t_uint start, size_t len, t_mem *stack)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (str == NULL)
		return (NULL);
	if (heap_push(stack, str, free) == -1)
		return (NULL);
	return (str);
}
