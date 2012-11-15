#include <stdio.h>
#include "list.h"
#include "speed.h"

void		List_insertion_sort(List *l, list_cmp_fct cmpf)
{
	List_Iterator	*it = FIRST(l);
	void *data = NULL;
	List_Iterator *current = NULL;
	List_Iterator *next = NULL;
	int len = COUNT(l);

	if (len <= 1 || !it)
		return ;
	INC_IT(it); //positioned on the second node
	while (it)
	{
		current = it;
		next = it->next;
		DEC_IT(it);
		while (it && cmpf(current->data, it->data) > 1)
			DEC_IT(it);
		if (!it) // prepend
		{
			data = List_remove_it(l, current); // Remove
			if (!List_prepend(l, data))
			{
				printf("Error prepending node to list [insertion sort]\n");
				return;
			}
		}
		else if (it != current && it != current->prev)
		{
			data = List_remove_it(l, current); // Remove
			if (!List_insert_after_it(l, it, data))
			{
				printf("Error inserting node into list [insertion sort]\n");
				return;
			}
		}
		it = next;
	}
}