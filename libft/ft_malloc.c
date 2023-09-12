/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/10 00:59:41 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t nmemb, size_t size, t_stackheap *stack, size_t *id)
{
	void	*mem;
	ssize_t	num;

	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	num = heap_push(stack, mem, free);
	if (num == -1)
		return (NULL);
	if (id != NULL)
		*id = num;
	return (mem);
}
