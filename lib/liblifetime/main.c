/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:00:31 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/12 21:38:53 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblifetime.h"
#include "../libft/libft.h"

void	heap_free2d(void *data)
{
	char	**d;
	int		i;

	d = (char **)data;
	i = 0;
	while (d[i])
		free(d[i]);
	free(d);
}

int	main(void)
{
	// t_stackheap	stack;
	// size_t		lt_a;
	// size_t		lt_ba;
	// size_t		lt_bb;

	// lt_a = heap_push(&stack,
	// 		(void *)ft_split("Hello, world! a", ' '), heap_free2d);
	// {
	// 	heap_borrow(&stack, lt_ba, lt_a);
	// 	lt_ba = heap_push(&stack,
	// 			(void *)ft_split("Hello, world! ba", ' '), heap_free2d);
	// 	lt_bb = heap_push(&stack,
	// 			(void *)ft_split("Hello, world! bb", ' '), heap_free2d);
	// 	heap_pop(&stack, lt_ba);
	// }
	// heap_get(&stack, lt_ba);
	// heap_pop(&stack, lt_a);
	return (0);
}
