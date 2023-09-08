/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/15 07:08:28 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_free(t_stackheap *stack, void *data)
{
	t_stacknode	*run;

	run = stack->last;
	while (run != NULL)
	{
		if (run->data == data)
		{
			if (run->prev != NULL)
				run->prev->next = run->next;
			if (run->next != NULL)
				run->next->prev = run->prev;
			run->destruct(run->data);
			free(run);
			break ;
		}
		run = run->prev;
	}
}
