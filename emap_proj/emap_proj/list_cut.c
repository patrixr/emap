#include <assert.h>
#include "list.h"

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

List		*List_concat(List *l1, List*l2)
{
	List_Iterator *it_tmp;

	if (!l1)
		return NULL;
	if (!l2 || !COUNT(l2))
	{
		free(l2);
		return l1;
	}

	if (!COUNT(l1))
	{
		while (COUNT(l2))
		{
			it_tmp = List_pop_first_it(l2);
			List_append_it(l1, it_tmp);
		}
	}
	else {
		l1->last->next = l2->first;
		l1->count += l2->count;
	}

	free(l2);
	return l1;
}