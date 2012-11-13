#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <stdint.h>
#include "application.h"

static void		display_project_information()
{
	printf("/******************--Welcome--******************/\n");
	printf("/******Team Number 1  |   Project : E_Map*******/\n\n");
	printf("/*********Date of creation : 2012/11/12*********/\n");
	printf("/***********************************************/\n\n\n");
}

static void		get_file_to_parse(char *path_to_file)
{
	printf("Please enter the path to the file you want to load : \n\n");
	scanf("%256s", path_to_file);
}

static void		display_menu_options()
{
	printf("\n\nPlease select your entry\n\n");
	printf("\t1. Read file\n");
	printf("\t2. Sort File\n");
	printf("\t3. Search\n");
	printf("\t4. Update\n");
	printf("\t0. Exit\n");
}

static List		*load_file(int argc, char **argv, application_t *app)
{
	char	path_to_file[256];

	if (argc >= 2)
	{
		app->file = parse_open_file(argv[1]);
	}
}


void		run(int argc, char **argv)
{
	application_t	app;

	app.file = NULL;
	app.road_list = NULL;

	display_project_information();



	//get_file_to_parse(path_to_file);

	while (1)
	{
		display_menu_options();
		//read_input_menu(input_value);
	}
}