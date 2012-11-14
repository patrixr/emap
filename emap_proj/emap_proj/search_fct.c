#include "list.h"
#include "emap.h"
#include "user_interface.h"

bool search_name(void *data, void *param)
{
	char	*name = (char*)param;
	road_t	*road = (road_t*)data;

	if (!road || !road->length || !param)
		return false;

	if (strstr(road->name, name))
		return true;
	return false;
}

bool search_link_id(void *data, void *param)
{
	search_interval_t *intv = (search_interval_t*)param;
	road_t	*road = (road_t*)data;

	if (!road || !road->length || !param)
		return false;
	
	if (road->link_id >= intv->a && road->link_id <= intv->b)
		return true;
	return false;
}

bool search_if_class(void *data, void *param)
{
	search_interval_t *intv = (search_interval_t*)param;
	road_t	*road = (road_t*)data;

	if (!road || !road->length || !param)
		return false;

	if (road->if_class >= intv->a && road->if_class <= intv->b)
		return true;
	return false;
}

bool search_crossings(void *data, void *param)
{
	search_interval_t *intv = (search_interval_t*)param;
	road_t	*road = (road_t*)data;

	if (!road || !road->length || !param)
		return false;

	if (road->crossings >= intv->a && road->crossings <= intv->b)
		return true;
	return false;
}

void	process_results(List *l)
{
	List_Iterator *it = NULL;
	int	count = 0;

	if (!l || !COUNT(l))
		return;
	it = FIRST(l);
	printf("Results : {%u entries}\n", COUNT(l));
	while (it && count++ < 11)
	{
		road_print(it->data);
		INC_IT(it);
	}
	if (count > 10)
	{
		printf("... \nLarge result set, logging in results.log\n");
		log_resutls(l, "./results.log");
	}
}