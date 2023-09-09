/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/10 00:53:36 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_remove(t_stackheap *stack, ssize_t id)
{
	ssize_t		i;
	t_stacknode	*run;

	run = stack->last;
	i = stack->id;
	while (i >= 0)
	{
		if (run->id == id)
		{
			if (run->prev != NULL)
				run->prev->next = run->next;
			if (run->next != NULL)
				run->next->prev = run->prev;
			run->destruct(run->data);
			free(run);
			break ;
		}
		i--;
	}
}
