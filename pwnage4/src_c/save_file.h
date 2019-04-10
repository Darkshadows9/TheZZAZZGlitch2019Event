#ifndef SAVE_FILE_INC
#define SAVE_FILE_INC

#include <stdlib.h>
#include <stdio.h>

#include "encoder.h"

#define SAVE_BANK_OFFSET	0x2000
#define SECRET_BYTES_OFFSET	BANK_OFFSET * 2 + 0x3

void saveFileRead(char* file_name, struct decryption_s *save_data);

void saveFileWrite(char* file_name, struct decryption_s *save_data);

#endif /*SAVE_FILE_INC*/
