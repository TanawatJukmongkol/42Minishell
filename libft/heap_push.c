/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/18 03:13:31 by Tanawat J.       ###   ########.fr       */
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
	if (!stack->begin)
	{
		node->next = NULL;
		node->prev = NULL;
		stack->begin = node;
		stack->last = node;
	}
	else
	{
		node->next = NULL;
		stack->last->next = node;
		stack->last->next->prev = stack->last;
		stack->last = stack->last->next;
	}
	return (stack->id);
}
