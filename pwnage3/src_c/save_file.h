#ifndef SAVE_FILE_INC
#define SAVE_FILE_INC

#include <stdlib.h>
#include <stdio.h>

#include "decryption.h"

#define BANK_OFFSET			0x6000
#define ITER_OUTER_OFFSET	BANK_OFFSET + 0x00ff
#define ITER_INNER_OFFSET	BANK_OFFSET + 0x0103
#define KEYGEN_OFFSET		BANK_OFFSET + 0x00f3
#define KEYGEN_MUL_OFFSET	BANK_OFFSET + 0x00f7
#define KEYGEN_ADD_OFFSET	BANK_OFFSET + 0x00fb
#define MAP_OFFSET			BANK_OFFSET + 0x0567

#define MAP_SIZE			0x0200

#define MOV32_FUNC			0x0084
#define ADD32_FUNC			0x0090
#define NON0_COND_FUNC		0x00a4
#define MUL32_FUNC			0x00c4
#define WRAP_FUNC			0x010f
#define ENTRY_POINT_FUNC	0x013a

#define RETURN_INSTRUCTION	0x00c9

void saveFileRead(char* file_name, struct decryption_s *save_data);

void saveFileWrite(char* file_name, struct decryption_s *save_data);

#endif /*SAVE_FILE_INC*/
