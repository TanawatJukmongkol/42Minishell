/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/10 00:58:25 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data))
{
	t_stacknode	*node;

	node = malloc(sizeof(t_stacknode));
	if (node == NULL)
		return (-1);
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
