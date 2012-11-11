#ifndef _BIT_OPERATIONS_H_
#define _BIT_OPERATIONS_H_

#include <stdint.h>

#define ENDIAN_SWAP16(b) \
		(((b & 0x00FF) << 8) | \
		((b & 0xFF00) >> 8))

#define ENDIAN_SWAP32(i)		\
	(							\
	((i & 0x000000FF) << 24) |	\
	((i & 0x0000FF00) << 8) |	\
	((i & 0x00FF0000) >> 8) |	\
	((i & 0xFF000000) >> 24))	

uint8_t		get_crossings(uint8_t byte);
/*< This function returns the number of crossings.
	Should be called with the 12th byte of the read data */

uint8_t		get_if_class(uint8_t byte);
/*< This function returns the IF class number.
	Should be called with the 12th byte of the read data */

uint8_t		get_name_flag(uint8_t byte);
/*< This function returns 0 if the name flag isn't set */

#endif // _BIT_OPERATIONS_H_