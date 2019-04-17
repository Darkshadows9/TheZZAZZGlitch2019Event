#include "encoder.h"

void setReadPointer(struct encoder_s *data, uint8_t *read_buffer)
{
	data->read_pointer = read_buffer;
	return;
}

void setChecksumByte(struct encoder_s *data, uint8_t checksum_byte)
{
	data->checksum_byte = checksum_byte;
	return;
}

void writeScrambleBuffer(struct encoder_s *data, uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	data->buffer_scramble[0] = a;
	data->buffer_scramble[1] = b;
	data->buffer_scramble[2] = c;
	data->buffer_scramble[3] = d;
	return;
}

void readBufferByte(struct encoder_s *data)
{
	data->buffer_output[0] = data->read_pointer[0];
	data->read_pointer++;
	return;
}

void scramble(struct encoder_s *data)
{
	data->buffer_scramble[0]++;
	data->buffer_scramble[1] ^= data->buffer_scramble[0] ^ data->buffer_scramble[3];
	data->buffer_scramble[2] += data->buffer_scramble[1];
	data->buffer_scramble[3] = ((data->buffer_scramble[2] >> 1) + data->buffer_scramble[3] ^ data->buffer_scramble[1]);
	data->buffer_output[0] = data->buffer_scramble[3];
	return;
}

void rotateBuffer(struct encoder_s *data)
{
	uint8_t wrapping_byte = data->buffer_output[0];
	for(uint16_t bc = 0; bc < OUTPUT_LENGTH; bc++)
	{
		data->buffer_output[bc] = data->buffer_output[bc + 1];
	}
	data->buffer_output[OUTPUT_LENGTH - 1] = wrapping_byte;
	return;
}

void updateChecksum(struct encoder_s *data)
{
	data->checksum_byte += data->buffer_output[0];
	return;
}

void writeChecksum(struct encoder_s *data)
{
	data->buffer_output[0] = data->checksum_byte;
	return;
}

void saveChecksumIncrementBufferReadPointer(struct encoder_s *data)
{
	data->read_pointer[0] = data->checksum_byte;
	data->read_pointer++;
	return;
}

void loadChecksumByte(struct encoder_s *data)
{
	data->checksum_byte = data->read_pointer[0];
	return;
}

void encoderRun(struct encoder_s *data)
{
	//loop0:
	setReadPointer(&data, &data->buffer_pokemon);
	setChecksumByte(&data, 0x7f);
	writeScrambleBuffer(&data, 0x2f, 0xe6, 0x10, 0x8c); //Little-endian 32-bit number
	for(uint8_t i = 0; i < 0x48; i++)
	{
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
		readBufferByte(&data);
		updateChecksum(&data);
		scramble(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop1:
	setReadPointer(&data, &data->buffer_event_flags);
	setChecksumByte(&data, 0xc2);
	writeScrambleBuffer(&data, 0xc2, 0x28, 0xf5, 0x6a);
	for(uint8_t i = 0; i < 0x14; i++)
	{
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop2:
	setReadPointer(&data, &data->buffer_money);
	for(uint8_t i = 0; i < 0x3; i++)
	{
		readBufferByte(&data);
		rotateBuffer(&data);
	}

	//loop3:
	setReadPointer(&data, &data->buffer_tms_hms);
	setChecksumByte(&data, 0x6);
	writeScrambleBuffer(&data, 0xa6, 0x5, 0x73, 0xef);
	for(uint8_t i = 0; i < 0x4c; i++)
	{
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop4:
	setReadPointer(&data, &data->buffer_pokemon_nicknames);
	writeScrambleBuffer(&data, 0x38, 0xec, 0x7f, 0x2a);
	setChecksumByte(&data, 0x3c);
	for(uint8_t i = 0; i < 0x21; i++)
	{
		readBufferByte(&data);
		updateChecksum(&data);
		scramble(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop5:
	setReadPointer(&data, &data->buffer_pokedex);
	setChecksumByte(&data, 0xe2);
	writeScrambleBuffer(&data, 0x15, 0x11, 0xfc, 0x4b);
	for(uint8_t i = 0; i < 0x40; i++)
	{
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop6:
	writeScrambleBuffer(&data, 0x7c, 0x38, 0x3f, 0xa2);
	setChecksumByte(&data, 0x16);
	setReadPointer(&data, &data->buffer_secret_bytes);
	for(uint8_t i = 0; i < 0x4; i++)
	{
		readBufferByte(&data);
		scramble(&data);
		updateChecksum(&data);
		updateChecksum(&data);
		rotateBuffer(&data);
	}
	writeChecksum(&data);
	rotateBuffer(&data);

	//loop7:
	setChecksumByte(&data, 0x0);
	setReadPointer(&data, &data->h_random_add);
	readBufferByte(&data);
	updateChecksum(&data);
	setReadPointer(&data, &data->buffer_DEADBEEF[0]);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	setReadPointer(&data, &data->h_random_sub);
	readBufferByte(&data);
	updateChecksum(&data);
	writeChecksum(&data);
	setReadPointer(&data, &data->buffer_DEADBEEF[1]);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	setReadPointer(&data, &data->f_divider_register);
	readBufferByte(&data);
	updateChecksum(&data);
	writeChecksum(&data);
	setReadPointer(&data, &data->buffer_DEADBEEF[2]);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	setReadPointer(&data, &data->f_timer_counter);
	readBufferByte(&data);
	updateChecksum(&data);
	writeChecksum(&data);
	setReadPointer(&data, &data->buffer_DEADBEEF[3]);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	writeScrambleBuffer(&data, 0xde, 0xad, 0xbe, 0xef);
	rotateBuffer(&data);
	rotateBuffer(&data);
	setChecksumByte(&data, 0x55);
	setReadPointer(&data, data->buffer_f350);
	saveChecksumIncrementBufferReadPointer(&data);
	saveChecksumIncrementBufferReadPointer(&data);
	for(uint8_t i = 0; i < 0x1AB; i++)
	{
		setReadPointer(&data, data->buffer_f350);
		loadChecksumByte(&data);
		updateChecksum(&data);
		saveChecksumIncrementBufferReadPointer(&data);
		loadChecksumByte(&data);
		updateChecksum(&data);
		saveChecksumIncrementBufferReadPointer(&data);
		scramble(&data);
		rotateBuffer(&data);
	}

	setChecksumByte(&data, 0xcc);
	setReadPointer(&data, &data->buffer_scramble[0]);
	updateChecksum(&data);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	updateChecksum(&data);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	updateChecksum(&data);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	updateChecksum(&data);
	saveChecksumIncrementBufferReadPointer(&data);
	rotateBuffer(&data);
	setReadPointer(&data, &data->buffer_f350);
	readBufferByte(&data);
	scramble(&data);
	rotateBuffer(&data);
	readBufferByte(&data);
	scramble(&data);
	rotateBuffer(&data);
	return;
}
