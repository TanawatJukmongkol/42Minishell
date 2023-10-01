/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/01 23:38:15 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_pop(t_stackheap *stack)
{
	t_stacknode	*node;

	if (stack->begin == NULL)
		return ;
	node = stack->last;
	if (node == stack->begin)
	{
		stack->begin = NULL;
		stack->last = NULL;
		stack->id = 0;
	}
	else
	{
		stack->last = stack->last->prev;
		stack->last->next = NULL;
		stack->id--;
	}
	node->destruct(node->data);
	free(node);
}
