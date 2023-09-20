/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/18 03:29:07 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_pop(t_stackheap *stack)
{
	t_stacknode	*node;

	if (!stack)
		return ;
	node = stack->last;
	if (!node || !node->data)
		return ;
	if (node == stack->begin)
	{
		stack->begin = NULL;
		stack->last = NULL;
	}
	else
	{
		stack->last = stack->last->prev;
		stack->last->next = NULL;
	}
	node->destruct(node->data);
	free(node);
}
