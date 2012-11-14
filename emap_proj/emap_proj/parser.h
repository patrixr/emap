#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <windows.h>
#include "emap.h"

/**
* Parse errors, to be completed
*/
typedef enum parse_status_e
{
P_CORRUPT, // Bad info
P_READ_ERROR, // unable to read the file
P_MISSING_DATA, //Byte count is under 12
P_INCOMPLETE_FILE, // early EOF
P_INVALID_NAME, // Non printable characters
P_COMPLETE, // Done reading the file
P_OK // Normal state (currently reading)
} parse_status_t;

typedef struct error_report_s
{
	parse_status_t 	err_type;
	const char *	err_message;
} error_report_t;

typedef struct emap_file_s
{
	FILE *stream;
	error_report_t last_error; // Null if no error occured
} emap_file_t;

//----------------------------------------------------------
// API
//----------------------------------------------------------

emap_file_t		*parse_open_file(const char *filename);
/*< Opens a file and allocates the file structure. Should be closed and
	freed with parse_close_file */

error_report_t	*parse_get_last_error(emap_file_t *file);
/*< When a parse error occurs, this function allows us to retrieve the last error */

parse_status_t	parse_get_next_road(emap_file_t *file, road_t *road_out);
/*< Reads the next road from the file, the returned status should be checked for errors */

void			parse_close_file(emap_file_t *file);
/*< Closes the file and frees the file structure */

int			save_to_file(List *l, const char *filename);

#endif // _PARSER_H_