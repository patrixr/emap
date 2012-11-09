#include "list.h"

// LOCAL
static void merge(List *a, List *b, List *out, list_cmp_fct cmpf)
{
	List_Iterator *it_tmp = NULL;

	if (!a || !b || !out)
		return;
	while (COUNT(a) || COUNT(b))
	{
		if (COUNT(a) && COUNT(b))
		{
			if (cmpf(FIRST(a)->data, FIRST(b)->data) == 1)
				List_append_it(out, List_pop_first_it(a));
			else
				List_append_it(out, List_pop_first_it(b));
		}
		else
		{
			if (COUNT(a) > 0)
				List_append_it(out, List_pop_first_it(a));
			else
				List_append_it(out, List_pop_first_it(b));
		}
	}
}

void		List_merge_sort(List *l, list_cmp_fct cmpf)
{
	List *out1;
	List *out2;

	if (COUNT(l) <= 1)
		return ;

	List_cut_half(l, &out1, &out2);
	
	List_merge_sort(out1, cmpf);
	List_merge_sort(out2, cmpf);

	merge(out1, out2, l, cmpf);

}

void		List_sort(List *l, list_cmp_fct cmpf)
{
	List_Iterator *it = FIRST(l);
	int i = 0;
	int sorted = 0;
	void *tmp = NULL;

	while (sorted != COUNT(l) - 1 && it)
	{
		if (cmpf(it->data, it->next->data) == -1)
		{
			tmp = it->data;
			it->data = it->next->data;
			it->next->data = tmp;
		}
		INC_IT(it);
		i++;
		if (i == COUNT(l) - 1 - sorted)
		{
			it = FIRST(l);
			sorted++;
			i = 0;
		}
	}

}