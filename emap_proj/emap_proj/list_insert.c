#include <assert.h>
#include "list.h"

bool		List_insert(List *l, void * data, int idx)
{
	List_Iterator *it = FIRST(l);
	List_Iterator *new_node = NULL;

	if (idx > COUNT(l))
		return false;

	if (idx == COUNT(l))
		List_append(l, data);
	else if (idx == 0)
		List_prepend(l, data);
	else
	{
		while (it && idx)
		{
			--idx;
			INC_IT(it);
		}
		if (!(new_node = (List_Iterator*) malloc(sizeof(*new_node))))
			return false;
		new_node->data = data;
		new_node->next = it;
		new_node->prev = it->prev;
		it->prev->next = new_node;
		it->prev = new_node;
		l->count++;
	}
	return true;
}

bool		List_insert_it(List *l, List_Iterator * new_node, int idx)
{
	List_Iterator *it = FIRST(l);

	if (!new_node)
		return false;

	if (idx > COUNT(l))
		return false;

	if (idx == COUNT(l))
		List_append_it(l, new_node);
	else if (idx == 0)
		List_prepend_it(l, new_node);
	else
	{
		while (it && idx)
		{
			--idx;
			INC_IT(it);
		}
		new_node->next = it;
		new_node->prev = it->prev;
		it->prev->next = new_node;
		it->prev = new_node;
		l->count++;
	}
	return true;
}

bool		List_insert_after_it(List *l, List_Iterator * it, void *data)
{
	List_Iterator *new_node = NULL;
	
	if (!it || !l)
	{
		return false;
	}

	new_node = (List_Iterator*)malloc(sizeof(List_Iterator));

	if (!new_node)
	{
		perror("malloc");
		return false;
	}

	new_node->prev = it;
	new_node->next = it->next;
	new_node->data = data;

	if (it != LAST(l))
		it->next->prev = new_node;
	else
		l->last = new_node;
	it->next = new_node;

	l->count++;

	return true;
}