#include <assert.h>
#include "list.h"

static List_Iterator		*List_pop_first_it(List *l)
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

void		List_cut_half(List *in, List **out1, List **out2)
{
	int		i = 0, total = COUNT(in);
	List_Iterator *it_tmp = NULL; 

	if (!in || !COUNT(in))
		return;

	*out1 = (List*) malloc(sizeof(*in));
	if (!*out1)
		return;

	*out2 = (List*) malloc(sizeof(*in));
	if (!*out2) {
		free(*out1);
		return;
	}

	(*out1)->count = 0;
	(*out2)->count = 0;
	(*out1)->first = NULL;
	(*out2)->first = NULL;
	(*out1)->last = NULL;
	(*out2)->last = NULL;


	while (i < total / 2)
	{
		it_tmp = List_pop_first_it(in);
		assert(it_tmp);
		List_append_it(*out1, it_tmp);
		i++;
	}
	while (i < total)
	{
		it_tmp = List_pop_first_it(in);
		assert(it_tmp);
		List_append_it(*out2, it_tmp);
		i++;
	}
}

void		List_merge(List *l1, List*l2, List *res)
{
	List_Iterator *it_tmp;

	if (!res || !l1 || !l2)
		return NULL;

	res->count = 0;
	res->first = NULL;
	res->last = NULL;
	
	while (COUNT(l1))
	{
		it_tmp = List_pop_first_it(l1);
		assert(it_tmp);
		List_append_it(res, it_tmp);
	}
	while (COUNT(l2))
	{
		it_tmp = List_pop_first_it(l2);
		assert(it_tmp);
		List_append_it(res, it_tmp);
	}
	
	free(l1);
	free(l2);
}