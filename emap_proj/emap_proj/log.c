#include "parser.h"
#include "emap.h"
#include "list.h"

void		log_resutls(List *l, const char *filename)
{
	List_Iterator	*it = FIRST(l);
	FILE			*file = NULL;
	road_t			*road = NULL;

	if (!it)
		return;

	file = fopen(filename, "w");
	if (!file)
		return;

	while (it)
	{
		road = (road_t*)it->data;
		if (road)
		{
			fprintf(file, "Road {LinkId:%u} {IfClass:%u} {Crossings:%u} {Name:%s}\n",
				road->link_id, road->if_class, road->crossings,
				(road->length ? road->name : ""));
		}
		INC_IT(it);
	}

	fclose(file);
}