/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblifetime.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:31:44 by tjukmong          #+#    #+#             */
/*   Updated: 2023/08/12 13:33:33 by Tanawat J.       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLIFETIME_H
# define LIBLIFETIME_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_stacknode
{
	size_t				id;
	void				*data;
	struct s_stacknode	*next;
	struct s_stacknode	*prev;
	void				(*destruct)(void *data);
}				t_stacknode;

typedef struct s_stackheap
{
	t_stacknode	*begin;
	t_stacknode	*last;
	size_t		id;
}				t_stackheap;

// Init a heap stack
void	heap_init(t_stackheap *stack);
// Pushes a new node to the stack
size_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data));
// Returns the node at index
void	heap_get(t_stackheap *stack, size_t id);
// Pops the last node from the stack
void	heap_pop(t_stackheap *stack);
// Remove the node at index
void	heap_remove(t_stackheap *stack, size_t id);
// Free all nodes
void	heap_purge(t_stackheap *stack);

#endif
