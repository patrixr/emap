#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "list.h"
#include "parser.h"
#include "emap.h"

/**
** Structure containing the main
** varaiables of the application
**/
typedef struct application_s
{
	emap_file_t		*file;
	List			*road_list;
} application_t;

// process.c
int		load_list_from_file(application_t *app);

#endif // APPLICATION