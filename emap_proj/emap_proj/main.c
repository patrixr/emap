#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "bit_operations.h"
#include "list.h"
#include "emap.h"
#include "parser.h"

int		main(int argc, char **argv)
{
	road_t	*road;
	List *list = NEW(List);
	int c = 0;
	parse_status_t	st;
	error_report_t	*err;
	emap_file_t *file = parse_open_file(argv[1]);
	if (!file) {
		printf("Unable to open file\n");
		return EXIT_FAILURE;
	}
	if (!list)
	{
		printf("oops\n");
		return EXIT_FAILURE;
	}
	road = (road_t*)malloc(sizeof(*road));
	if (!road)
	{
		printf("OOM\n");
		return EXIT_FAILURE;
	}
	st = parse_get_next_road(file, road);
	while (st == P_OK)
	{
		st = parse_get_next_road(file, road);
		if (st == P_OK)
		{
			List_append(list, road);
			road = (road_t*)malloc(sizeof(*road));
			if (!road)
			{
				printf("OOM\n");
				return EXIT_FAILURE;
			}
		}
		else
			free(road);
	}
	if (st != P_COMPLETE)
		printf("%s\n", file->last_error.err_message);

	printf("List has %i elements\n", COUNT(list));
	List_foreach(list, &road_print);
	printf("SORT\n");
	List_insertion_sort(list, &cmp_link_id);
	List_foreach(list, &road_print);

	printf("FREEING ALL\n");
	while (COUNT(list))
	{
		free(list->first->data);
		List_remove_it(list, FIRST(list));
	}
	return EXIT_SUCCESS;
}