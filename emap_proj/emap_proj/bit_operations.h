#ifndef _BIT_OPERATIONS_H_
#define _BIT_OPERATIONS_H_

#include <stdint.h>

uint8_t		get_crossings(uint8_t byte);
/*< This function returns the number of crossings.
	Should be called with the 12th byte of the read data */

uint8_t		get_if_class(uint8_t byte);
/*< This function returns the IF class number.
	Should be called with the 12th byte of the read data */


#endif // _BIT_OPERATIONS_H_