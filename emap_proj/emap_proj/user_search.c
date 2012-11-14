#include "application.h"
#include "user_interface.h"

static search_interval_t	get_interval()
{
	search_interval_t	intv;
	unsigned int tmp;


	printf("\n [Search] Value interval \n");
	printf("Lowest value :\n");
	scanf("%u", &(intv.a));
	printf("Highest value :\n");
	scanf("%u", &(intv.b));
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
	int method = 0;
	search_interval_t intv;
	unsigned int tmp;
	List *res = NULL;
	char name[256];

	printf("\nSearch for : \n\n");
	printf("\t1. LinkID\n");
	printf("\t2. If_Class\n");
	printf("\t3. Name\n");
	printf("\t4. Crossings\n");

	while (1)
	{
		scanf("%1d", &method);
		if (method < 1 || method > 4)
			printf("Unknown entry\n\n");
		else
		{
			if (method == 1)
			{
				intv = get_interval();
				res = List_get_all(app->road_list, search_link_id, &intv); 
				break;
			}
			else if (method == 2)
			{
				intv = get_interval();
				res = List_get_all(app->road_list, search_if_class, &intv);
				break;
			}
			else if (method == 3)
			{
				printf("\nPlease enter a name \n");
				scanf("%s", name);
				res = List_get_all(app->road_list, search_name, name);
				break;
			}
			else if (method == 4)
			{
				intv = get_interval();
				res = List_get_all(app->road_list, search_crossings, &intv);
				break;
			}
		}
	}
	process_results(res);
}
