#include "list.h"
#include "application.h"
#include "bit_operations.h"

static void		write_in_dat_file(void* data, void *param)
{
	FILE *file = (FILE*)param;
	road_t	*road = (road_t*)data;
	uint16_t	datalen;
	uint32_t	linkid = ENDIAN_SWAP32(road->link_id);
	uint16_t	len;
	uint32_t	last_bytes = 0;

	datalen = (road->name ? road->length + 2: 0) + 12;
	len = (road->name ? ENDIAN_SWAP16(datalen - 12) : 0);

	datalen = ENDIAN_SWAP16(datalen);

	
	fwrite(&datalen, sizeof(datalen), 1, file);
	fwrite(&linkid, sizeof(linkid), 1, file);
	fwrite(&len, sizeof(len), 1, file);

	if (ENDIAN_SWAP16(datalen) > 12)
	{
		last_bytes = 1;
		last_bytes = last_bytes << 3;
	}
	last_bytes |= road->crossings;
	last_bytes = last_bytes << 4;
	last_bytes |= road->if_class;
	last_bytes = ENDIAN_SWAP32(last_bytes);

	fwrite(&last_bytes, sizeof(last_bytes), 1, file);
	if (road->name && road->length)
		fwrite(road->name, road->length + 2, 1, file);
}	

int			save_to_file(List *l, const char *filename)
{
	FILE *file = fopen(filename, "wb");
	
	if (!file)
	{
		perror("fopen");
		return -1;
	}
	if (l)
		List_foreach_param(l, &write_in_dat_file, file);
	fclose(file);
	return 0;
}