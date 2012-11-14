#ifndef _SPEED_H_
#define _SPEED_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BEGIN_SPEED_RECORD start = clock();		

#define STOP_SPEED_RECORD	\
	finish = clock();		\
	duration = (double)(finish - start) / CLOCKS_PER_SEC; \
	printf( "\nProcessed in : %f seconds\n", duration );

#define INIT_SPEED_RECORD clock_t start, finish; double  duration;

#endif