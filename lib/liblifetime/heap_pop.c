
#include "liblifetime.h"

void	heap_pop(t_stackheap *stack)
{
	t_stacknode	*last;

	last = stack->last;
	if (last == stack->begin)
	{
		stack->begin->destruct(stack->begin->data);
		free(stack->begin);
		stack->begin = NULL;
		stack->last = NULL;
	}
	else
	{
		stack->last = stack->last->prev;
		last->destruct(last->data);
		free(last);
	}
}

