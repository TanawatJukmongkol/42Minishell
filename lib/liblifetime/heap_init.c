
#include "liblifetime.h"

void	heap_init(t_stackheap *stack)
{
	stack->begin = NULL;
	stack->last = NULL;
	stack->id = 0;
}

