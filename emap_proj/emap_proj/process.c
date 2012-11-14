#include <windows.h>
#include <stdlib.h>
#include "application.h"

int		load_list_from_file(application_t *app)
{
	parse_status_t	st;
	road_t			*road;
	int				count = 0;

	if ((app->road_list = NEW(List)) == NULL)
	{
		perror("malloc");
		return -1;
	}
	st = P_OK;
	while (st == P_OK)
	{
		road = (road_t*)malloc(sizeof(*road));
		if (!road) {
			perror("malloc");
			return -1;
		}

		st = parse_get_next_road(app->file, road);

		if (st == P_OK)
			List_append(app->road_list, road);
		else
			free(road);
		if (count++ % 200 == 0) {
			printf(".");
		}
	}
	printf("\n");
	if (st != P_COMPLETE)
	{
		printf("== Error : %s\n", app->file->last_error.err_message);
		return -1;
	}
	return 0;
}
