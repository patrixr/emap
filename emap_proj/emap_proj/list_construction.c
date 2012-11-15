#include "list.h"

/*
CONSTRUCTION
*/

List		*List_new()
{
  List		*l;

  l = malloc(sizeof(*l));
  if (!l)
    return NULL;
  l->count = 0;
  l->first = NULL;
  l->last = NULL;
  return l;
}

/*
DESTRUCTION
*/

static void	List_it_delete(List_Iterator *it)
{
  if (!it)
    return;
  if (!IS_LAST(it))
    List_it_delete(NEXT(it));
  free(it);
}

void		List_delete(List *l)
{
	List_Iterator *it;
	List_Iterator *next;

	if (!l)
		return;

	it = FIRST(l);
	while (it)
	{
		next = NEXT(it);
		free(it);
		it = next;
	}
	free(l);
}
