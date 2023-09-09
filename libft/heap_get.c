/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/09/10 00:53:25 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*heap_get(t_stackheap *stack, ssize_t id)
{
	t_stacknode	*tmp;

	tmp = stack->last;
	while (tmp && id >= tmp->id)
	{
		if (tmp->id == id)
			return (tmp->data);
		tmp = tmp->prev;
	}
	return (NULL);
}
