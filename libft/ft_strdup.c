/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:31:58 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/16 05:06:22 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Duplicates the string *s into malloc'd string.
char	*ft_strdup(const char *s)
{
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_memcpy(str, s, len);
	return (str);
}

char	*ft_strdup_heap(const char *s, t_stackheap *stack)
{
	char	*str;

	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	if (heap_push(stack, str, free) == -1)
		return (NULL);
	return (str);
}
