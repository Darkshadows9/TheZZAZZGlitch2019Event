#include "save_file.h"

void saveFileRead(char* file_name, struct decryption_s *save_data)
{
	FILE *save_file = fopen(file_name, "r+");
	if(!save_file)
	{
		printf("Failed to open save file. Exiting.\n");
		exit(EXIT_FAILURE);
	}
	fseek(save_file, 0, SEEK_END);
	size_t buffer_size = ftell(save_file);
	fseek(save_file, 0, SEEK_SET);
	uint8_t *buffer = calloc(buffer_size, sizeof(uint8_t));
	fread(buffer, sizeof(uint8_t), buffer_size, save_file);
	save_data->iter_outer = buffer[ITER_OUTER_OFFSET + 3] << 24 | buffer[ITER_OUTER_OFFSET + 2] << 16 | buffer[ITER_OUTER_OFFSET + 1] << 8 | buffer[ITER_OUTER_OFFSET];
	save_data->iter_inner = buffer[ITER_INNER_OFFSET + 3] << 24 | buffer[ITER_INNER_OFFSET + 2] << 16 | buffer[ITER_INNER_OFFSET + 1] << 8 | buffer[ITER_INNER_OFFSET];
	save_data->keygen = buffer[KEYGEN_OFFSET + 3] << 24 | buffer[KEYGEN_OFFSET + 2] << 16 | buffer[KEYGEN_OFFSET + 1] << 8 | buffer[KEYGEN_OFFSET];
	save_data->keygen_mul = buffer[KEYGEN_MUL_OFFSET + 3] << 24 | buffer[KEYGEN_MUL_OFFSET + 2] << 16 | buffer[KEYGEN_MUL_OFFSET + 1] << 8 | buffer[KEYGEN_MUL_OFFSET];
	save_data->keygen_add = buffer[KEYGEN_ADD_OFFSET + 3] << 24 | buffer[KEYGEN_ADD_OFFSET + 2] << 16 | buffer[KEYGEN_ADD_OFFSET + 1] << 8 | buffer[KEYGEN_ADD_OFFSET];
	for(size_t i = 0; i < MAP_SIZE; i++)
	{
		save_data->map[i] = buffer[MAP_OFFSET + i];
	}
	free(buffer);
	fclose(save_file);
	return;
}

void saveFileWrite(char *file_name, struct decryption_s *save_data)
{
	FILE *save_file = fopen(file_name, "r+");
	if(!save_file)
	{
		printf("Failed to open file. Dumping map to terminal as a failsafe:\n");
		for(size_t i = 0; i < MAP_SIZE; i++)
		{
			printf("%x", save_data->map[i]);
		}
		printf("\nDone.\n");
		exit(EXIT_FAILURE);
	}
	fseek(save_file, 0, SEEK_END);
	size_t buffer_size = ftell(save_file);
	fseek(save_file, 0, SEEK_SET);
	uint8_t *buffer = calloc(buffer_size, sizeof(uint8_t));
	fread(buffer, sizeof(uint8_t), buffer_size, save_file);
	for(size_t i = 0; i < MAP_SIZE; i++)
	{
		buffer[MAP_OFFSET + i] = save_data->map[i];
	}
	buffer[ENTRY_POINT_FUNC] = RETURN_INSTRUCTION;
	fseek(save_file, 0, SEEK_SET);
	fwrite(buffer, sizeof(uint8_t), buffer_size, save_file);
	free(buffer);
	fclose(save_file);
	return;
}