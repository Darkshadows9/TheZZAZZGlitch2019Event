#ifndef ENCODER_INC
#define ENCODER_INC

#include <stdbool.h>
#include <stdint.h>

#define U32_BYTE_SIZE				0x4
#define POKEMON_LENGTH				0x90
#define EVENT_FLAGS_LENGTH 			0x14
#define MONEY_LENGTH				0x3
#define TMS_HMS_LENGTH				0x97
#define POKEMON_NICKNAMES_LENGTH	0x21
#define POKEDEX_LENGTH				0x40
#define OUTPUT_LENGTH				0x1b0
#define F350_LENGTH					0x2

struct encoder_s
{
	uint8_t buffer_output[OUTPUT_LENGTH]; //$c800-$c9b0, write to $3:a100-$3:a2b0
	uint8_t buffer_scramble[U32_BYTE_SIZE]; //$2:adb1-$2:adb4
	uint8_t buffer_pokemon[POKEMON_LENGTH]; //$fcdf-$fd6e, read from $1:a86d-$1:a8fc
	uint8_t buffer_event_flags[EVENT_FLAGS_LENGTH]; //$fa7a-$fa8d, read from $1:a608-$1:a61b
	uint8_t buffer_money[MONEY_LENGTH]; //$f84e-$f850, read from $1:a3dc-$1:a3de
	uint8_t buffer_tms_hms[TMS_HMS_LENGTH]; //$f859-$f8ef, read from $1:a3e7-$1:a47d
	uint8_t buffer_pokemon_nicknames[POKEMON_NICKNAMES_LENGTH]; //$de41-$de61, read from $1:a9cf-$1:a9ef
	uint8_t buffer_pokedex[POKEDEX_LENGTH]; //$de99-$ded8, read from $1:aa27-$1:aa66
	uint8_t buffer_secret_bytes[U32_BYTE_SIZE]; //$2:a003
	uint8_t buffer_DEADBEEF[U32_BYTE_SIZE]; //$2:b16b
	uint8_t buffer_f350[F350_LENGTH]; //$f350
	uint8_t checksum_byte; //$2:adb0
	uint8_t h_random_add; //$ffe1
	uint8_t h_random_sub; //$ffe2
	uint8_t f_divider_register; //$ff04
	uint8_t f_timer_counter; //$ff05, f_timer_counter % 0x08 = (f_divider_register - 0x30) / 4
	uint8_t *read_pointer;
};

void encoderRun(struct encoder_s *data);

void decoderRun(struct encoder_s *data);

#endif /*ENCODER_INC*/
