#include "emap.h"


uint8_t		get_crossings(uint8_t byte)
{
	// Remove name flag
	uint8_t noflag = byte << 1;

	// Return IF class
	return noflag >> 5;
}

uint8_t		get_if_class(uint8_t byte)
{
	byte = byte << 4;
	return byte >> 4;
}