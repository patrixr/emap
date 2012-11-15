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
	printf("\t0. Cancel\n");

	method = get_entry('0', '4');
	if (method == '1')
		return &cmp_link_id;
	if (method == '2')
		return &cmp_if_class;
	if (method == '3')
		return &cmp_crossings;
	if (method == '4')
		return &cmp_name;
	return NULL;
}

void	sorting_method(application_t *app)
{
	int	method = 0;
	list_cmp_fct fct = NULL;
	INIT_SPEED_RECORD

	printf("\nPlease select a sorting method : \n\n");
	printf("\t1. Quick Sort\n");
	printf("\t2. Bubble Sort\n");
	printf("\t3. Merge Sort\n");
	printf("\t4. Insertion Sort\n");
	printf("\t0. Back\n");

	method = get_entry('0', '4');
	if (method == '0')
		return;
	fct = get_sorting_function();
	if (!fct)
		return ;
	BEGIN_SPEED_RECORD
	if (method == '3')
		List_merge_sort(app->road_list, fct);
	if (method == '2')
	{
		if (COUNT(app->road_list) > 200 &&
			user_decide("Large list : This sort might be slow. Continue ?"))
			List_sort(app->road_list, fct);
		else
			return;
	}
	if (method == '4')
		List_insertion_sort(app->road_list, fct);
	if (method == '1')
		List_quick_sort(app->road_list, fct);
	STOP_SPEED_RECORD
	return;
}