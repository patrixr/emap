#include <stdlib.h>
#include <io.h>
#include <windows.h>
#include "application.h"
#include "user_interface.h"

static search_interval_t	get_interval()
{
	search_interval_t	intv;
	unsigned int tmp;


	printf("\n [Search] Value interval \n");
	printf("Lowest value :\n");
	scanf_s("%u", &(intv.a));
	printf("Highest value :\n");
	scanf_s("%u", &(intv.b));
	printf(" %u  %u\n", intv.a, intv.b);
	if (intv.a > intv.b)
	{
		tmp = intv.a;
		intv.a = intv.b;
		intv.b = tmp;
	}
	return intv;
}

void		search_method(application_t *app)
{
	char method = 'q';
	search_interval_t intv;
	List *res = NULL;
	char name[256];
	int r;

	printf("\nSearch for : \n\n");
	printf("\t1. LinkID\n");
	printf("\t2. If_Class\n");
	printf("\t3. Name\n");
	printf("\t4. Crossings\n");
	printf("\t0. Back\n");

	method = get_entry('0', '4');
	if (method == '1') {
		intv = get_interval();
		res = List_get_all(app->road_list, search_link_id, &intv);
	}
	else if (method == '2') {
		intv = get_interval();
		res = List_get_all(app->road_list, search_if_class, &intv);
	}
	else if (method == '3') {
		printf("\nPlease enter a name \n");
		r = _read(0, name, 256);
		while (name[0] == '\n')
			r = _read(0, name, 256);
		if (r <= 0)
			return;
		else
			name[r - 1] = '\0';
		res = List_get_all(app->road_list, search_name, name);
	}
	else if (method == '4') {
		intv = get_interval();
		res = List_get_all(app->road_list, search_crossings, &intv);
	}
	else
		return;
	process_results(res);
}
