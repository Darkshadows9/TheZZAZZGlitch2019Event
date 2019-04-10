#ifndef DECRYPTION_INC
#define DECRYPTION_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct decryption_s {
	uint32_t	iter_outer;
	uint32_t	iter_inner;
	uint32_t	keygen;
	uint32_t	keygen_mul;
	uint32_t	keygen_add;
	size_t		map_size;
	uint8_t		map[];
};

void decryptionRun(struct decryption_s *data);

void decryptionRunReverse(struct decryption_s *data);

#endif /*DECRYPTION_INC*/
