#include "decryption.h"

int64_t eea(int64_t a, int64_t b) //extendedEuclideanAlgorithm
{
	int64_t c;
	if(b > a)
	{
		c = b;
		b = a;
		a = c;
	}
	int64_t invp = 0;
	int64_t inv = 1;

	while(b != 0)
	{
		c = a / b;
		int64_t temp = invp - c * inv;
		invp = inv;
		inv = temp;

		c = a % b;
		a = b;
		b = c;
	}

	return invp;
}

void decryptionStepBlock(struct decryption_s *data)
{
	uint16_t var = data->keygen & 0xff;
	uint16_t var_mul = (data->keygen >> 16) & 0xff;
	uint16_t var_add = data->keygen >> 24;
	for(uint16_t i = 0; i < data->iter_inner; i++)
	{
		var = (var >> 1) * var_mul + var_add;
		data->map[i % data->map_size] ^= var & 0xff;
	}
	return;
}

void decryptionRun(struct decryption_s *data)
{
	for(size_t i = 0; i < data->iter_outer; i++)
	{
		printf("step %x of %x...\n", i, data->iter_outer);
		decryptionStepBlock(data);
		data->keygen = data->keygen * data->keygen_mul + data->keygen_add;
	}
}

void decryptionRunReverse(struct decryption_s *data)
{
	uint32_t keygen_mul_inverse = (uint32_t) eea(data->keygen_mul, data->keygen_add);
	for(size_t i = 0; i < 0x80000000 - data->iter_outer; i++)
	{
		printf("step %x of %x...\n", i, data->iter_outer);
		data->keygen = (data->keygen - data->keygen_add) * keygen_mul_inverse;
		decryptionStepBlock(data);
	}
}
