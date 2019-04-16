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
	for(uint16_t bc = 0; bc < BUFFER_OUTPUT_LENGTH; bc++)
	{
		data->buffer_output[bc] = data->buffer_output[bc + 1];
	}
	data->buffer_output[BUFFER_OUTPUT_LENGTH - 1] = wrapping_byte;
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

void HaltAndFinalize()
{

}

void encoderRun(struct encoder_s *data)
{
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

}

void decoderRun(struct encoder_s *data)
{

}