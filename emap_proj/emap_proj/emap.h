#ifndef _EMAP_H_
#define _EMAP_H_

#include <stdint.h>

//-----------------------------------------------------
// DATA STRUCTURE
//
// example :
// 0019   0000 0852    000B    1011   0110   A3B1...  
//  (1)      (2)        (3)     (4)    (5)    (6)
//
// (1) Number of bytes defining the road (self included), cannot be under 12
// (2) LinkID of the road
// (3) Sizeof the roadname (can be 0 if the road doesn't have a name)
// (4) The first bit is a flag name, to determine whether the road has a name
//		the 3 other bits define the number of crossings
// (5) IF Class number
// (6) Name (if any)
//-----------------------------------------------------

typedef struct road_s
{
	char		*name;
	uint16_t	length; // Can be 0
	uint32_t	link_id;
	uint16_t	if_class;
	uint16_t	crossings;
} road_t;


#endif // _EMAP_H_