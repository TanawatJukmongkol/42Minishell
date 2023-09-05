
#include "liblifetime.h"

size_t	heap_push(t_stackheap *stack, void *data, void (*destruct)(void *data))
{
	if (!stack->begin)
	{
		stack->begin = malloc(sizeof(t_stacknode));
		stack->begin->next = NULL;
		stack->begin->prev = NULL;
		stack->begin->data = data;
		stack->begin->destruct = destruct;
		stack->begin->id = ++stack->id;
	}
	else
	{
		stack->last->next = malloc(sizeof(t_stacknode));
		if (!stack->last->next)
			heap_purge(stack);
		stack->last->next->id = ++stack->id;
		stack->last->next->data = data;
		stack->last->next->destruct = destruct;
		stack->last->next->prev = stack->last;
		stack->last = stack->last->next;
	}
	return (stack->id);
}

