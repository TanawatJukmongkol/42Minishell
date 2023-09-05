#include "liblifetime.h"

void	*heap_get(t_stackheap *stack, size_t id)
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
