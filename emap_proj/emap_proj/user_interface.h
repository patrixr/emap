#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#define SORT '1'
#define SEARCH '2'
#define UPDATE '3'
#define PRINT '4'
#define EXIT '0'

#define	QUICK_SORT 1
#define BUBBLE_SORT 2
#define MERGE_SORT 3
#define INSERTION_SORT 4

#include "application.h"

void		run(int argc, char **argv);
void		sorting_method(application_t *app);
void		search_method(application_t *app);
char		get_entry(char min, char max);
int			user_decide(const char *question);

typedef struct search_interval_s
{
	unsigned int a;
	unsigned int b;
} search_interval_t;

#endif //_USER_INTERFACE_H_