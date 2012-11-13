#include <assert.h>
#include <stdio.h>
#include "list.h"

static void	quick_sort(List *l,
		List_Iterator *first,
		List_Iterator *last,
		list_cmp_fct cmpf)
{
	List_Iterator *pivot = last;
	List_Iterator *it = first;
	List_Iterator *next = NULL;
	void *data = NULL;
	last = NULL;

	if (!it || !pivot || it == pivot)
	{
		return;
	}


	while (it != pivot)
	{
		assert(it != NULL);
		next = it->next;
		if (cmpf(it->data, pivot->data) < 0)
		{
			if (it == first)
				first = it->next;
			data = List_remove_it(l, it);
			List_insert_after_it(l, pivot, data);
			if (last == NULL)
				last = pivot->next;
		}
		it = next;
	}
	quick_sort(l, first, pivot->prev, cmpf);
	quick_sort(l, pivot->next, last, cmpf);
}

void		List_quick_sort(List *l, list_cmp_fct cmpf)
{

	quick_sort(l, FIRST(l), l->last, cmpf);
}