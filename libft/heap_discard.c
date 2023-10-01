/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_discard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/01 22:23:00 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_discard(t_stackheap *stack, void *mem)
{
	t_stacknode	*run;

	run = stack->last;
	while (run != NULL)
	{
		if (run->data == mem)
		{
			if (run->prev != NULL)
				run->prev->next = run->next;
			if (run->next != NULL)
				run->next->prev = run->prev;
			if (run == stack->begin)
				stack->begin = stack->begin->next;
			if (run == stack->last)
				stack->last = stack->last->prev;
			free(run);
			break ;
		}
		run = run->prev;
	}
}