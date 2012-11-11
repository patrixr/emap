#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "bit_operations.h"
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

#define TO_INT(ptr) *((int*)ptr)

int		int_cmp(void *data, void *data2)
{
	if (TO_INT(data) > TO_INT(data2))
		return -1;
	if (TO_INT(data) < TO_INT(data2))
		return 1;
	return 0;
}

int		main(int argc, char **argv)
{
	road_t	road;
	parse_status_t	st;
	error_report_t	*err;
	emap_file_t *file = parse_open_file(argv[1]);
	if (!file) {
		printf("Unable to open file\n");
		return EXIT_FAILURE;
	}
	st = parse_get_next_road(file, &road);
	while (st == P_OK)
	{
		printf("P_OK\n");
		printf("Crossings %u\n", road.crossings);
		printf("If Class %u\n", road.if_class);
		printf("Name Length : %u\n", road.length);
		printf("Link id %u\n", road.link_id);
		st = parse_get_next_road(file, &road);
		if (st != P_OK) printf("NOT OK\n");
		printf("\n========================\n");
	}
	if (st != P_COMPLETE)
		printf("%s\n", file->last_error.err_message);
	
	/*FILE *f = NULL;
	uint16_t	length = 0;
	uint32_t linkid = 0;
	uint16_t name_len = 0;
	uint8_t a = 182;


	f = fopen(argv[1], "rb");
	if (!f)
		printf("could not open file\n");
	else {
		fread(&length, 2, 1, f);
		//length = length >> 8;
		//fread(&length, 1, 1, f);
		printf("Length == %u\n", length);
		printf("Length (swapped) == %u\n", ENDIAN_SWAP16(length));
		fread(&linkid, 4, 1, f);
		printf("Link id == %u\n", linkid);
		printf("Link id (swapped) == %u\n", ENDIAN_SWAP32(linkid));
		
		fread(&name_len, 2, 1, f);
		printf("name length = %u\n", name_len);
		printf("name length (swapped) = %u\n", ENDIAN_SWAP16(name_len));

		fread(&linkid, 4, 1, f);
		printf("last 4 bytes == %u\n", linkid);
		printf("last 4 bytes (swapped) == %u\n", ENDIAN_SWAP32(linkid));

		fread(&length, 2, 1, f);
		//length = length >> 8;
		//fread(&length, 1, 1, f);
		printf("\n\n\nLength == %u\n", length);
		printf("Length (swapped) == %u\n", ENDIAN_SWAP16(length));
		

	}

	
	printf("%s\n", argv[1]);
	printf("byte : %u\n", a);

	//a = a << 1;
	//a = a >> 1;

	printf("crossings : %u\n", get_crossings(a));
	printf("if class : %u\n", get_if_class(a));

	*/
	/*List *list = NEW(List);
	List *out1 = NULL;
	List *out2 = NULL;

	List *res_set = NULL;

	int a=1,b=2,c=3,d=4,e=5,f=6,g=7;

	int h = 42;

	List_append(list, &b);
	List_append(list, &c);
	List_append(list, &d);
	List_append(list, &f);
	List_append(list, &e);
	List_append(list, &a);
	List_append(list, &g);


	List_foreach(list, &print_data);
	printf("COUNT : %i\n", COUNT(list));

	printf("------   M SORT --------\n");

	List_merge_sort(list, &int_cmp);

	List_foreach(list, &print_data);
	printf("COUNT : %i\n", COUNT(list));

	List_cut_half(list, &out1, &out2);
	printf("------   HALF 1 --------\n");
	List_foreach(out1, &print_data);
	printf("COUNT : %i\n", COUNT(out1));
	printf("------   HALF 2 --------\n");
	List_foreach(out2, &print_data);
	printf("COUNT : %i\n", COUNT(out2));

		printf("------   ORIGINAL LIST --------\n");
	List_foreach(list, &print_data);
	printf("COUNT : %i\n", COUNT(list));

	printf("------   RE-MERGE --------\n");
	printf("AAA\n");
	List_concat(out1, out2, list);
	printf("AAA %p\n", list);
	List_foreach(list, &print_data);
	printf("COUNT : %i\n", COUNT(list));

	*/
	/*
		printf("------prepended 42--------\n");

	//List_remove_it(list, FIRST(list));
	List_prepend(list, &h);
	List_foreach(list, &print_data);
	
	printf("COUNT : %i\n", COUNT(list));

	List_sort(list, &int_cmp);
	printf("------bubble sorted --------\n");
	
	List_foreach(list, &print_data);
	

	printf("COUNT : %i\n", COUNT(list));

	printf("---------- searched for all under 5 ---------\n");
	res_set = List_get_all(list, &is_under_five, NULL);
	List_foreach(res_set, &print_data);
	
	printf("COUNT : %i\n", COUNT(list));
	printf("------removed all under 5--------\n");
	List_remove(list, &is_under_five, NULL);
	List_foreach(list, &print_data);

	printf("COUNT : %i\n", COUNT(list));*/

//sad

#ifdef _DEBUG
	system("pause");
#endif

	return EXIT_SUCCESS;
}