#include <string.h>
#include "emap.h"

#define ROAD(p) ((road_t*)(p))

int			cmp_link_id(void *data1, void *data2)
{
	road_t *r1 = ROAD(data1);
	road_t *r2 = ROAD(data2);

	if (!data1 || !data2)
		return 0;

	if (r1->link_id < r2->link_id)
		return 1;
	if (r1->link_id > r2->link_id)
		return -1;
	return 0;
}

int			cmp_if_class(void *data1, void *data2)
{
	road_t *r1 = ROAD(data1);
	road_t *r2 = ROAD(data2);

	if (!data1 || !data2)
		return 0;

	if (r1->if_class < r2->if_class)
		return 1;
	if (r1->if_class > r2->if_class)
		return -1;
	return 0;
}

int			cmp_crossings(void *data1, void *data2)
{
	road_t *r1 = ROAD(data1);
	road_t *r2 = ROAD(data2);

	if (!data1 || !data2)
		return 0;

	if (r1->crossings < r2->crossings)
		return 1;
	if (r1->crossings > r2->crossings)
		return -1;
	return 0;
}

static int	my_strcasecmp(char *s1, char *s2)
{
	while (tolower(*s1) == tolower(*s2))
    {
      if (*s1 == '\0' || *s2 == '\0')
		break;
      s1++;
      s2++;
    }
  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}

int			cmp_name(void *data1, void *data2)
{
	road_t *r1 = ROAD(data1);
	road_t *r2 = ROAD(data2);
	int res = 0;

	if (!data1 || !data2)
		return 0;

	if (!r1->name && !r2->name)
		return 0;
	if (!r1->name && r2->name)
		return 1;
	if (r1->name && !r2->name)
		return -1;
	res = -1 * my_strcasecmp(r1->name, r2->name);
	if (res > 0)
		return 1;
	if (res < 0)
		return -1;
	return 0;
}