#include "save_file.h"

void saveFileRead(char* file_name, struct encoder_s *save_data)
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

	for(size_t i = 0; i < POKEMON_LENGTH; i++)
	{
		save_data->buffer_pokemon[i] = 0x00 + i;
	}
	for(size_t i = 0; i < EVENT_FLAGS_LENGTH; i++)
	{
		save_data->buffer_event_flags[i] = 0x91 + i;
	}
	for(size_t i = 0; i < MONEY_LENGTH; i++)
	{
		save_data->buffer_money[i] = 0xa6 + i;
	}
	for(size_t i = 0; i < TMS_HMS_LENGTH; i++)
	{
		save_data->buffer_tms_hms[i] = 0xa9 + i;
	}
	for(size_t i = 0; i < POKEMON_NICKNAMES_LENGTH; i++)
	{
		save_data->buffer_pokemon_nicknames[i] = 0x42 + i;
	}
	for(size_t i = 0; i < POKEDEX_LENGTH; i++)
	{
		save_data->buffer_pokedex[i] = 0x64 + i;
	}
	for(size_t i = 0; i < U32_BYTE_SIZE; i++)
	{
		save_data->buffer_secret_bytes[i] = buffer[SECRET_BYTES_OFFSET + i];
	}
	save_data->buffer_DEADBEEF[0] = 0xde;
	save_data->buffer_DEADBEEF[1] = 0xad;
	save_data->buffer_DEADBEEF[2] = 0xbe;
	save_data->buffer_DEADBEEF[3] = 0xef;
	save_data->checksum_byte = buffer[CHECKSUM_BYTE_OFFSET];
	save_data->buffer_f350[0] = F350_VALUE;
	save_data->buffer_f350[1] = F351_VALUE;
	save_data->h_random_add = H_RANDOM_ADD_SAMPLE;
	save_data->h_random_sub = H_RANDOM_SUB_SAMPLE;
	save_data->f_divider_register = F_DIVIDER_REGISTER_SAMPLE;
	save_data->f_timer_counter = F_TIMER_COUNTER_SAMPLE;

	free(buffer);
	fclose(save_file);
	return;
}

void saveFileWrite(char *file_name, struct encoder_s *save_data)
{
	FILE *save_file = fopen(file_name, "r+");
	if(!save_file)
	{
		printf("Failed to open file. Dumping data to terminal as a failsafe:\n");
		//Do that stuff the print says
		printf("\nDone.\n");
		exit(EXIT_FAILURE);
	}
	fseek(save_file, 0, SEEK_END);
	size_t buffer_size = ftell(save_file);
	fseek(save_file, 0, SEEK_SET);
	uint8_t *buffer = calloc(buffer_size, sizeof(uint8_t));
	fread(buffer, sizeof(uint8_t), buffer_size, save_file);

	//Write the final data to the buffer.

	fseek(save_file, 0, SEEK_SET);
	fwrite(buffer, sizeof(uint8_t), buffer_size, save_file);
	free(buffer);
	fclose(save_file);
	return;
}
