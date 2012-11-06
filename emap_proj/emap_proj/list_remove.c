#include "list.h"

void		*List_remove_it(List *l, List_Iterator *it)
{
	l->count--;
}

bool		List_remove(List *l, list_predicate fct, void *param)
{
	List_Iterator *it = FIRST(l);

	if (!it)
		return;
	while (it)
	{
		if (fct(it->data, param))
			List_remove_it(l, it);
		it = NEXT(it);
    }
}