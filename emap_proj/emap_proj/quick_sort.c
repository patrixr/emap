#include "list.h"

static void	quick_sort(List *l,
		List_Iterator *first,
		List_Iterator *last,
		list_cmp_fct cmpf)
{
	/*List_Iterator *pivot = last;
	List_Iterator *it = first;
	List_Iterator *next = NULL;
	void *data = NULL;

	while (it != pivot)
	{
		next = it->next;
		if (cmpf(it->data, pivot->data) < 0)
		{
			data = List_remove_it(l, it);
			List_insert_after_it(l, pivot, data);
		}
	}*/
	
}

void		list_quick_sort(List *l, list_cmp_fct cmpf)
{
	quick_sort(l, FIRST(l), LAST(l), cmpf);
}