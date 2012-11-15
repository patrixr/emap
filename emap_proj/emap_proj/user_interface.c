#include <stdio.h>
#include <direct.h>
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
	r = _read(0, path_to_file, 256);
	if (r <= 0)
		path_to_file[0] = '\0';
	else
		path_to_file[r - 1] = '\0';
}

int		user_decide(const char *question)
{
	char		r;

	printf("%s [y/n]\n", question);
	_read(0, &r, 1);
	while (r != 'Y' && r != 'y' && r != 'N' && r != 'n')
	{
		_read(0, &r, 1);
	}
	if (r == 'Y' || r == 'y')
	{
		while (r != '\n')
			_read(0, &r, 1);
		return 1;
	}
	while (r != '\n')
		_read(0, &r, 1);
	return 0;
}

static void		display_menu_options()
{
	printf("\n\n\t[MAIN]\n");
	printf("\tPlease select your entry\n\n");
	printf("\t1. Sort File\n");
	printf("\t2. Search\n");
	printf("\t3. Update\n");
	printf("\t4. Print\n");
	printf("\t0. Exit\n");
}

char			get_entry(char min, char max)
{
	char		method;
	int			invalid = 1;

	while (invalid)
	{
		_read(0, &method, 1);
		while (method == '\n')
			_read(0, &method, 1);
		if (method < min || method > max) {
			printf("Unknown entry : %c\n\n", method);
		}
		else
			return method;
		while (method != '\n')
			_read(0, &method, 1);
	}
	return method;
}


static void		free_road(void *data)
{
	if (data)
		free(data);
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
				return -1;
	}
	while (!app->file)
	{
		memset(path_to_file, 0, 256);
		get_file_to_parse(path_to_file);
		app->file = parse_open_file(path_to_file);
		printf("--> |%s|\n", path_to_file);
		if (!app->file)
			if (!user_decide("Unable to load file, do you wish to select another ?"))
				return -1;
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

void		run(int argc, char **argv)
{
	application_t	app;
	char			input_value;
	
	app.file = NULL;
	app.road_list = NULL;
	app.directory = _getcwd( NULL, 0 );

	/**
	* INIT
	*/
	display_project_information();

	if (load_file(argc, argv, &app) < 0)
	{
		printf("== Exiting...\n");
		return;
	}
	printf ("== File loaded successfully\n");

	/**
	* MAIN LOOP
	*/
	while (1)
	{
		display_menu_options();
		input_value = get_entry('0', '4');
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
			printf("== Saving data to %s\\out.dat...", (app.directory ? app.directory : ""));
			if (save_to_file(app.road_list, "./out.dat") < 0)
				printf("failed");
			printf("\n");
		}
		else if (input_value == PRINT) {
			printf("== Saving list to %s\\roads.log...", (app.directory ? app.directory : ""));
			log_resutls(app.road_list, "./roads.log");
		}
	}

	/**
	* CLEANUP
	*/
	List_foreach(app.road_list, &free_road);
	List_delete(app.road_list);
	if (app.directory)
		free(app.directory);
}