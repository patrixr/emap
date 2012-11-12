#include <stdio.h>
#include "emap.h"

void		road_print(void *data)
{
	road_t	*r = (road_t*)data;

	printf("Road {IF:%u}\t{ID:%3.u}\t{CROSSINGS:%u}\n",
		r->if_class,
		r->link_id,
		r->crossings);
}