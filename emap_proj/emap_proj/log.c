#include "parser.h"
#include "emap.h"
#include "list.h"

void		log_resutls(List *l, const char *filename)
{
	List_Iterator	*it = FIRST(l);
	FILE			*file = NULL;
	road_t			*road = NULL;
	unsigned int	i = 0;

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
			fprintf(file, "%u. Road {LinkId:%u} {IfClass:%u} {Crossings:%u} {Name:%s}\n",
				i++, road->link_id, road->if_class, road->crossings,
				(road->length ? road->name : ""));
		}
		INC_IT(it);
	}

	fclose(file);
}