#include "list.h"

List_Iterator		*List_pop_first_it(List *l)
{
	List_Iterator *it = FIRST(l);

	if (!COUNT(l))
		return NULL;

	if (l->count == 1)
	{
		l->first = NULL;
		l->last = NULL;
	}
	else
	{
		l->first = it->next;
		it->next->prev = NULL;
	}
	l->count--;
	return it;
}