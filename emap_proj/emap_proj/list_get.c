#include "list.h"

void		*List_get(List *l, int idx)
{
	List_Iterator *it = FIRST(l);

	if (COUNT(l) < idx)
		return NULL;

	while (idx && it) {
		--idx;
		INC_IT(it);
	}
	if (it && !idx)
		return it->data;
	return NULL;
}

List_Iterator		*List_get_it(List *l, int idx)
{
	List_Iterator *it = FIRST(l);

	if (COUNT(l) < idx)
		return NULL;

	while (idx && it) {
		--idx;
		INC_IT(it);
	}
	if (it && !idx)
		return it;
	return NULL;
}

void		*List_get_first(List *l, list_predicate fct, void * param)
{
	List_Iterator *it = FIRST(l);

	while (it)
	{
		if (fct(it->data, param))
			return it->data;
		INC_IT(it);
	}
	return NULL;
}

List		*List_get_all(List *l, list_predicate fct, void *param)
{
	List	*result_set = NEW(List);
	List_Iterator *it = FIRST(l);

	if (!result_set)
		return NULL;

	while (it)
	{
		if (fct(it->data, param))
			List_append(result_set, it->data);
		INC_IT(it);
	}
	if (!COUNT(result_set))
	{
		free(result_set);
		return NULL;
	}
	return result_set;
}