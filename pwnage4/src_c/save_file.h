#ifndef SAVE_FILE_INC
#define SAVE_FILE_INC

#include <stdlib.h>
#include <stdio.h>

#include "encoder.h"

#define BANK_OFFSET							0x2000
#define SCRAMBLE_OFFSET						BANK_OFFSET * 2 + 0xdb1
#define POKEMON_OFFSET						BANK_OFFSET + 0x086d
#define EVENT_FLAGS_OFFSET					BANK_OFFSET + 0x0608
#define MONEY_OFFSET						BANK_OFFSET + 0x03dc
#define TMS_HMS_OFFSET						BANK_OFFSET + 0x03e7
#define POKEMON_NICKNAMES_OFFSET			BANK_OFFSET + 0x09cf
#define POKEDEX_OFFSET						BANK_OFFSET + 0x0a27a
#define SECRET_BYTES_OFFSET					BANK_OFFSET * 2 + 0x0003
#define DEADBEEF_OFFSET						BANK_OFFSET * 2 + 0x116b
#define CHECKSUM_BYTE_OFFSET				BANK_OFFSET * 2 + 0x0db0
#define OUTPUT_OFFSET						BANK_OFFSET * 3 + 0x0100
#define UPDATE_CHECKSUM_BYTE_OFFSET			BANK_OFFSET * 2 + 0x0dcc

#define F350_VALUE							0x04
#define F351_VALUE							0xcd

#define UPDATE_CHECKSUM_BYTE_FINAL_VALUE	0xae

#define H_RANDOM_ADD_SAMPLE					0xc3
#define H_RANDOM_SUB_SAMPLE					0xf6
#define F_DIVIDER_REGISTER_SAMPLE			0xf5
#define F_TIMER_COUNTER_SAMPLE				0Xcc

void saveFileRead(char* file_name, struct encoder_s *save_data);

void saveFileWrite(char* file_name, struct encoder_s *save_data);

#endif /*SAVE_FILE_INC*/
