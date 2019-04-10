#include "encoder.h"

//read_pointer++;
void readBufferByte()
{

}

void scramble()
{

}

void rotateBuffer()
{

}

void writeLong()
{

}

void updateChecksum()
{

}

void writeChecksum()
{

}

void djnz()
{

}

void saveChecksumByteAndBufferReadPointer()
{

}

void loadChecksumByte()
{

}

void HaltAndFinalize()
{

}

void encoderRun(struct encoder_s *data)
{
	uint8_t *read_pointer = &data->buffer_pokemon;
	uint8_t checksum_byte = 0x7f;
	uint8_t scrambling_buffer[4] = {0x2f, 0xe6, 0x10, 0x8c};
	for(uint8_t i = 0; i < 0x48; i++)
	{
		uint8_t scramble_byte = read_pointer[i];
	}
}

void decoderRun(struct encoder_s *data)
{

}