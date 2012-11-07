#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "list.h"
#include "emap.h"
#include "parser.h"

void	print_data(void *data)
{
	int *a = (int*)data;
	printf("%i\n", *a);
}

bool	is_under_five(void *data, void *param)
{
	if (*((int*)data) < 5)
		return true;
	return false;
}

int		main()
{
	List *list = NEW(List);

	List *res_set = NULL;

	int a=1,b=2,c=3,d=4,e=5,f=6,g=7;

	int h = 42;

	List_append(list, &a);
	List_append(list, &b);
	List_append(list, &c);
	List_append(list, &d);
	List_append(list, &e);
	List_append(list, &f);
	List_append(list, &g);

	List_foreach(list, &print_data);
	
	printf("COUNT : %i\n", COUNT(list));
	printf("------prepended 42--------\n");

	//List_remove_it(list, FIRST(list));
	List_prepend(list, &h);
	List_foreach(list, &print_data);
	
	printf("COUNT : %i\n", COUNT(list));

	printf("---------- searched for all under 5 ---------\n");
	res_set = List_get_all(list, &is_under_five, NULL);
	List_foreach(res_set, &print_data);
	
	printf("COUNT : %i\n", COUNT(list));
	printf("------removed all under 5--------\n");
	List_remove(list, &is_under_five, NULL);
	List_foreach(list, &print_data);

	printf("COUNT : %i\n", COUNT(list));

//sad

#ifdef _DEBUG
	system("pause");
#endif

	return EXIT_SUCCESS;
}