#include "application.h"
#include "speed.h"
#include "user_interface.h"

static list_cmp_fct		get_sorting_function()
{
	int	method = 0;

	printf("\nSort by : \n\n");
	printf("\t1. Link ID\n");
	printf("\t2. IF Class\n");
	printf("\t3. Crossings\n");
	printf("\t4. Name\n");

	while (1)
	{
		scanf("%1d", &method);
		if (method < 1 || method > 4)
			printf("Unknown entry\n\n");
		else
		{
			if (method == 1)
				return &cmp_link_id;
			if (method == 2)
				return &cmp_if_class;
			if (method == 3)
				return &cmp_crossings;
			if (method == 4)
				return &cmp_name;
		}
	}
}

void	sorting_method(application_t *app)
{
	int	method = 0;

	printf("\nPlease select a sorting method : \n\n");
	printf("\t1. Quick Sort\n");
	printf("\t2. Bubble Sort\n");
	printf("\t3. Merge Sort\n");
	printf("\t4. Insertion Sort\n");

	while (1)
	{
		scanf("%1d", &method);
		if (method < 1 || method > 4)
			printf("Unknown entry\n\n");
		else
		{
			if (method == MERGE_SORT)
				List_merge_sort(app->road_list, get_sorting_function());
			if (method == BUBBLE_SORT)
				List_sort(app->road_list, get_sorting_function());
			if (method == INSERTION_SORT)
				List_insertion_sort(app->road_list, get_sorting_function());
			if (method == QUICK_SORT)
				printf("This sort has not been implemented yet\n");
			break;
		}
	}
}
