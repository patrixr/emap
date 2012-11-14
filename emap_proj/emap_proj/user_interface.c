#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <stdint.h>
#include "user_interface.h"
#include "application.h"

//------------------------------------------
// MISC
//------------------------------------------

static void		display_project_information()
{
	printf("/******************--Welcome--******************/\n");
	printf("/******Team Number 1  |   Project : E_Map*******/\n\n");
	printf("/*********Date of creation : 2012/11/12*********/\n");
	printf("/***********************************************/\n\n\n");
}

static void		get_file_to_parse(char *path_to_file)
{
	int r;

	printf("Please enter the path to the file you wish to load : \n\n");
	r = read(0, path_to_file, 256);
	if (r <= 0)
		path_to_file[0] = '\0';
	else
		path_to_file[r - 1] = '\0';
}

static int		user_decide(const char *question)
{
	char		r;

	printf("%s [y/n]\n", question);
	scanf("%c", &r);
	while (r != 'Y' && r != 'y' && r != 'N' && r != 'n')
	{
		scanf("%c", &r);
	}
	if (r == 'Y' || r == 'y')
		return 1;
	return 0;
}

static void		display_menu_options()
{
	printf("\n\nPlease select your entry\n\n");
	printf("\t1. Sort File\n");
	printf("\t2. Search\n");
	printf("\t3. Update\n");
	printf("\t4. Print\n");
	printf("\t0. Exit\n");
}

// INITIALIZATION

static int		load_file(int argc, char **argv, application_t *app)
{
	char		path_to_file[256];

	/**
	* Opening file
	*/
	if (argc >= 2) {
		app->file = parse_open_file(argv[1]);
		if (!app->file)
			if (!user_decide("Unable to load file, do you wish to select another ?"))
				return;
	}
	while (!app->file)
	{
		memset(path_to_file, 0, 256);
		get_file_to_parse(path_to_file);
		app->file = parse_open_file(path_to_file);
		if (!app->file)
			if (!user_decide("Unable to load file, do you wish to select another ?"))
				return ;
	}
	/**
	* Reading file
	*/
	if (load_list_from_file(app) < 0)
	{
		printf("== An error occured, exiting\n");
		parse_close_file(app->file);
		return -1;
	}
	parse_close_file(app->file);
	return 0;
}

static char	read_input_menu()
{
	int		is_valid = 0;
	char	input_value;


	while (!is_valid)
	{
		display_menu_options();
		scanf("%c", &input_value);
		while (input_value == '\n')
			scanf("%c", &input_value);
		if (input_value != SORT &&
			input_value != SEARCH &&
			input_value != UPDATE &&
			input_value != PRINT &&
			input_value != EXIT)
		{
			printf("Unknown entry : %c \n\n", input_value);
		}
		else
			is_valid = 1;
	}
	return input_value;
}


void		run(int argc, char **argv)
{
	application_t	app;
	char			input_value;
	app.file = NULL;
	app.road_list = NULL;

	display_project_information();

	if (load_file(argc, argv, &app) < 0)
	{
		perror("load file");
		return;
	}
	printf ("== File loaded successfully\n");
	while (1)
	{
		input_value = read_input_menu();
		if (input_value == EXIT) {
			printf("== Exiting...\n");
			break;
		}
		else if (input_value == SORT)
			sorting_method(&app);
		else if (input_value == SEARCH)
			search_method(&app);
		else if (input_value == UPDATE)
		{
			printf("Saving data to out.dat...\n");
			save_to_file(app.road_list, "./out.dat");
		}
		else if (input_value == PRINT) {
			List_foreach(app.road_list, &road_print);
			printf("< %u entries >", COUNT(app.road_list));
		}
	}
}