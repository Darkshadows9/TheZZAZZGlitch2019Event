#ifndef ENCODER_INC
#define ENCODER_INC

#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SCRAMBLE_LENGTH			0x04
#define BUFFER_POKEMON_LENGTH			0x90
#define BUFFER_EVENT_FLAGS_LENGTH 		0x14
#define BUFFER_MONEY_LENGTH				0x03
#define BUFFER_TMS_HMS_LENGTH			0x97
#define BUFFER_POKEMON_NICKNAMES_LENGTH	0x21
#define BUFFER_POKEDEX_LENGTH			0x40
#define BUFFER_SECRET_BYTES_LENGTH		0x04
#define BUFFER_DEADBEEF_LENGTH			0x04

struct encoder_s
{
	uint8_t buffer_scramble[BUFFER_SCRAMBLE_LENGTH]; //adb1
	uint8_t buffer_pokemon[BUFFER_POKEMON_LENGTH]; //fcdf
	uint8_t buffer_event_flags[BUFFER_EVENT_FLAGS_LENGTH]; //fa7a
	uint8_t buffer_money[BUFFER_MONEY_LENGTH]; //f84e
	uint8_t buffer_tms_hms[BUFFER_TMS_HMS_LENGTH]; //f859
	uint8_t buffer_pokemon_nicknames[BUFFER_POKEMON_NICKNAMES_LENGTH]; //de41
	uint8_t buffer_pokedex[BUFFER_POKEDEX_LENGTH]; //de99
	uint8_t buffer_secret_bytes[BUFFER_SECRET_BYTES_LENGTH]; //2:a003
	uint8_t buffer_DEADBEEF[0x04]; //b16b
	uint8_t h_random_add; //ffe1
	uint8_t h_random_sub; //ffe2
	uint8_t f_divider_register; //ff04
	uint8_t f_timer_counter; //ff05, f_timer_counter % 0x08 = (f_divider_register - 0x30) / 4
};

void encoderRun(struct encoder_s *data);

void decoderRun(struct encoder_s *data);

#endif /*ENCODER_INC*/
