/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/15 07:08:59 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data))
{
	t_stacknode	*node;

	node = malloc(sizeof(t_stacknode));
	if (node == NULL)
		return (heap_purge(stack), -1);
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
		stack->last->next = node;
		stack->last->next->prev = stack->last;
		stack->last = stack->last->next;
	}
	return (stack->id);
}
