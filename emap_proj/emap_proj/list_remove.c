#include "list.h"

void		*List_remove_it(List *l, List_Iterator *it)
{
	void *tmp;

	if (!l || !l->count || !it)
		return NULL;

	tmp = it->data;

	if (l->count == 1)
	{
		l->first = NULL;
		l->last = NULL;
	}
	else if (it == FIRST(l)) // The node is the first of the list
	{
		l->first = it->next;
		it->next->prev = NULL;
	}
	else if (it == LAST(l)) // The node is the last
	{
		l->last = it->prev;
		it->prev->next = NULL;
	}
	else // The node is somewhere in the middle
	{
		it->next->prev = it->prev;
		it->prev->next = it->next;
	}
	free(it);
	l->count--;
	return tmp;
}

bool		List_remove(List *l, list_predicate fct, void *param)
{
	List_Iterator *it = FIRST(l);
	List_Iterator *tmp = NULL;

	if (!it)
		return false;
	while (it)
	{
		tmp = NEXT(it);
		if (fct(it->data, param))
		{
			List_remove_it(l, it);
			return true;
		}
		it = tmp;
    }
	return false;
}