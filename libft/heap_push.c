/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/01 20:09:03 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data))
{
	t_stacknode	*node;

	if (!stack || !data || !destruct)
		return (heap_purge(stack), exit(-1), -1);
	node = malloc(sizeof(t_stacknode));
	if (node == NULL)
		return (destruct(data), -1);
	node->data = data;
	node->destruct = destruct;
	node->id = ++stack->id;
	node->prev = NULL;
	node->next = NULL;
	if (!stack->begin)
	{
		stack->begin = node;
		stack->last = node;
	}
	else
	{
		node->next = NULL;
		stack->last->next = node;
		node->prev = stack->last;
		stack->last = node;
	}
	return (stack->id);
}
