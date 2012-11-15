#include <assert.h>
#include <stdio.h>
#include "list.h"

static void	quick_sort(List *l,
		/*List_Iterator *first,
		List_Iterator *last,*/
		list_cmp_fct cmpf)
{
/*	
	A LITTLE MORE OPTIMIZED BUT BUGGED VERSION

	List_Iterator *pivot = last;
	List_Iterator *it = first;
	List_Iterator *next = NULL;
	void *data = NULL;
	last = NULL;

	if (!it || !pivot || it == pivot || !pivot->prev || !it->next)
	{
		return;
	}

	while (it != pivot)
	{
		next = it->next;
		if (cmpf(it->data, pivot->data) <= 0)
		{
			if (it == first)
				first = it->next;
			data = List_remove_it(l, it);
			assert(data);
			assert(List_insert_after_it(l, pivot, data));
			if (last == NULL)
				last = pivot->next;
		}
		it = next;
	}
	quick_sort(l, first, pivot->prev, cmpf);
	quick_sort(l, pivot->next, last, cmpf);*/

	void *pivot;
	int cmp = 0;
	List *less = NEW(List);
	List *greater = NEW(List);
	List *equal = NEW(List);
	List_Iterator *it;

	if (!less || !greater || !equal)
	{
		perror("malloc");
		return ;
	}
	if (COUNT(l) <= 1)
		return ;

	it = List_get_it(l, (COUNT(l)/2 - 1));
	pivot = it->data;
	List_remove_it(l, it);
	while (COUNT(l))
	{
		it = List_pop_first_it(l);
		cmp = cmpf(it->data, pivot);
		if (cmp > 0)
			List_append_it(less, it);
		else if (cmp < 0)
			List_append_it(greater, it);
		else
			List_append_it(equal, it);

	}
	// SUBLISTS
	if (COUNT(less)) {
		quick_sort(less, cmpf);
		List_concat(l, less);
	}
	else
		free(less);

	// 
	List_append(l, pivot);
	
	if (COUNT(equal)) {
		List_concat(l, equal);
	}
	else
		free(equal);


	if (COUNT(greater)) {
		quick_sort(greater, cmpf);
		List_concat(l, greater);
	}
	else
		free(greater);

}

void		List_quick_sort(List *l, list_cmp_fct cmpf)
{
	quick_sort(l,/* FIRST(l), l->last,*/ cmpf);
}