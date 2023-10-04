/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tponutha <tponutha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/10/01 23:51:38 by tponutha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	heap_init(t_stackheap *stack)
{
	stack->begin = NULL;
	stack->last = NULL;
	stack->id = 0;
}

// #include "./libft/libft.h"
// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	t_stackheap	mem;
// 	int			i;
// 	int			j;
// 	int			samp[4];
// 	char		**box;
// 	char		*tmp;
// 	char		*line;

// 	i = 1;
// 	j = 0;
// 	samp[0] = 3;
// 	samp[1] = 0;
// 	samp[2] = 10;
// 	samp[3] = 5;
// 	heap_init(&mem);
// 	// box = malloc(sizeof(char *) * 4);
// 	// heap_push(&mem, box, free);
// 	// box[0] = NULL;
// 	// box[1] = NULL;
// 	// box[2] = NULL;
// 	// box[3] = NULL;
// 	printf("CHECK 1\n");
// 	while (i < ac)
// 	{
// 		line = ft_strdup(av[i]);
// 		heap_push(&mem, line, free);
// 		if (i == 1)
// 			tmp = line;
// 		if (i == samp[0] || i == samp[1] || i == samp[2] || i == samp[3])
// 		{
// 			box[j] = line;
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("CHECK 2\n");
// 	i = 0;
// 	heap_free(&mem, tmp);
// 	// while (i < j)
// 	// {
// 	// 	heap_free(&mem, box[i]);
// 	// 	i++;
// 	// }
// 	printf("CHECK 3\n");
// 	i = 0;
// 	while (i < 3)
// 	{
// 		heap_pop(&mem);
// 		i++;
// 	}
// 	printf("CHECK 4\n");
// 	heap_purge(&mem);
// 	heap_purge(&mem);
// 	return (0);
// }