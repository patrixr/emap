#include <assert.h>
#include "parser.h"
#include "bit_operations.h"

#define RETURN_PARSE_ERROR(f, status, msg)											\
			f->last_error.err_message = msg; f->last_error.err_type = status;		\
			return status;

emap_file_t		*parse_open_file(const char *filename)
{
	emap_file_t	*f = (emap_file_t*)malloc(sizeof(*f));
	if (!f)
		return NULL;
	
	f->last_error.err_message = "";
	f->last_error.err_type = P_OK;
	f->stream = fopen(filename, "rb");
	if (!f->stream)
	{
		free(f);
		return NULL;
	}
	return f;
}

error_report_t	*parse_get_last_error(emap_file_t *file)
{
	return (file ? &file->last_error : NULL);
}

static parse_status_t	emap_read(emap_file_t *file, void *buffer, size_t size)
{
	if (!fread(buffer, size, 1, file->stream))
	{
		if (feof(file->stream))
			return P_COMPLETE;
		if (ferror(file->stream))
			RETURN_PARSE_ERROR(file, P_READ_ERROR, "An error occured while reading the file\n");
		RETURN_PARSE_ERROR(file, P_MISSING_DATA, "Road data is incomplete\n");
	}
	return P_OK;
}

parse_status_t	parse_get_next_road(emap_file_t *file, road_t *road_out)
{
	parse_status_t	st;
	int				offset = 0;
	uint8_t			has_name = 0;
	uint8_t			buffer[12];
	uint16_t		data_len = 0;
	uint32_t		tmp = 0;
	uint8_t			last_byte = 0;

	assert(file && road_out && file->stream);

	if ((st = emap_read(file, buffer, 12)) != P_OK)
		return st;

	// DATA SIZE
	memcpy(&data_len, buffer, sizeof(data_len));
	offset += sizeof(data_len);
	data_len = ENDIAN_SWAP16(data_len);
	//printf("Data len asd : %u\n", data_len);
	if (data_len < 12)
	{
		RETURN_PARSE_ERROR(file, P_MISSING_DATA, "Road data is corrupt or incomplete\n");
	}
	printf("Data len : %u\n", data_len);

	// LINK ID
	memcpy(&road_out->link_id, buffer + offset, sizeof(road_out->link_id));
	offset += sizeof(road_out->link_id);
	road_out->link_id = ENDIAN_SWAP32(road_out->link_id);
	assert(offset < 12);
	//printf("Link id %u\n", road_out->link_id);

	// NAME LENGTH
	memcpy(&road_out->length, buffer + offset, sizeof(road_out->length));
	offset += sizeof(road_out->length);
	road_out->length = ENDIAN_SWAP16(road_out->length);
	assert(offset < 12);

	printf("name len %u\n", road_out->length);

	// NAME FLAG, crossings and IF CLASS
	memcpy(&tmp, buffer + offset, sizeof(tmp));
	offset += sizeof(road_out->length);

	last_byte = tmp;
	road_out->crossings = get_crossings(last_byte);
	road_out->if_class = get_if_class(last_byte);
	has_name = get_name_flag(last_byte);
	
	printf("has name %u, data_len %u, crossings %u\n", has_name, data_len, road_out->crossings);
	
	if ((has_name && data_len == 12) ||
		(!has_name && data_len > 12)) {
			
	//printf("-------------------\n");
		//RETURN_PARSE_ERROR(file, P_CORRUPT, "Corrupt File : Data length and Flag name conflict\n");
	}
	if (data_len == 12)
	{
		road_out->length = 0;
		road_out->name = NULL;
	}
	else
	{
		road_out->name = (char*)malloc(road_out->length);
		printf("Reading name\n");
		if (!road_out->name) RETURN_PARSE_ERROR(file, P_READ_ERROR, "Malloc fail : out of memory\n");
		if ((st = emap_read(file, road_out->name, road_out->length)) != P_OK)
		{
			return st;
		}
	}
	printf("Returned road without error\n");
	return P_OK;
}

void			parse_close_file(emap_file_t *file)
{
	if (file && file->stream)
	{
		fclose(file->stream);
	}
}