Flow: (pc = AE17)
de = B0B3
sp = AE18
AE21 = 00
AE26 = AE2C

Bytecode (@de):
	SetReadPtr 0xfcdf
	InitChecksumByte 0x7f
	WriteLong 0x8c10e62f
.loop0 ; @ 0xb0bd
	ReadBufferByte
	Scramble
	UpdateChecksum
	RotateBuffer
	ReadBufferByte
	UpdateChecksum2
	Scramble
	RotateBuffer
	Djnz 0x48, 0xb0bd
	WriteChecksum
	RotateBuffer

	SetReadPtr 0xfa7a
	InitChecksumByte 0xc2
	WriteLong 0x6af528c2
.loop1 ; @ 0xb0d5
	ReadBufferByte
	Scramble
	UpdateChecksum2
	RotateBuffer
	Djnz 0x14, 0xb0d5
	WriteChecksum
	RotateBuffer

	SetReadPtr 0xf84e
.loop2 ; @ 0xb0e2
	ReadBufferByte
	RotateBuffer
	Djnz 0x3, 0xb0e2

	SetReadPtr 0xf859
	InitChecksumByte 0x6
	WriteLong 0xef7305a6
.loop3 ; @ 0xb0f2
	ReadBufferByte
	Scramble
	UpdateChecksum2
	RotateBuffer
	ReadBufferByte
	Scramble
	UpdateChecksum
	RotateBuffer
	Djnz 0x4c, 0xb0f2
	WriteChecksum
	RotateBuffer

	SetReadPtr 0xde41
	WriteLong 0x2a7fec38
	InitChecksumByte 0x3c
.loop4 ; @ 0xb10a
	ReadBufferByte
	UpdateChecksum
	Scramble
	RotateBuffer
	Djnz 0x21, 0xb10a
	WriteChecksum
	RotateBuffer

	SetReadPtr 0xde99
	InitChecksumByte 0xe2
	WriteLong 0x4bfc1115
.loop5 ; @ 0xb11e
	ReadBufferByte
	Scramble
	UpdateChecksum
	RotateBuffer
	Djnz 0x40, 0xb11e
	WriteChecksum
	RotateBuffer

	WriteLong 0xa23f387c
	InitChecksumByte 0x16
	SetReadPtr 0xa003
.loop6 ; @ 0xb132
	ReadBufferByte
	Scramble
	UpdateChecksum2
	UpdateChecksum
	RotateBuffer
	Djnz 0x4, 0xb132
	WriteChecksum
	RotateBuffer

	InitChecksumByte 0x0
	SetReadPtr 0xffe1
	ReadBufferByte
	UpdateChecksum
	SetReadPtr 0xb16b
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	SetReadPtr 0xffe2
	ReadBufferByte
	UpdateChecksum2
	WriteChecksum
	SetReadPtr 0xb16c
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	SetReadPtr 0xff04
	ReadBufferByte
	UpdateChecksum
	WriteChecksum
	SetReadPtr 0xb16d
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	SetReadPtr 0xff05
	ReadBufferByte
	UpdateChecksum2
	WriteChecksum
	SetReadPtr 0xb16e
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	WriteLong 0xefbeadde
	RotateBuffer
	RotateBuffer
	InitChecksumByte 0x55
	SetReadPtr 0xf350
	saveChecksumIncrementBufferReadPointer
	saveChecksumIncrementBufferReadPointer
.loop7 ; @ 0xb178
	SetReadPtr 0xf350
	loadChecksumByte
	UpdateChecksum
	saveChecksumIncrementBufferReadPointer
	loadChecksumByte
	UpdateChecksum2
	saveChecksumIncrementBufferReadPointer
	Scramble
	RotateBuffer
	Djnz 0xd5, 0xb178
	Djnz 0xd6, 0xb178

	InitChecksumByte 0xcc
	SetReadPtr 0xadb1
	UpdateChecksum2
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	UpdateChecksum2
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	UpdateChecksum2
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	UpdateChecksum2
	saveChecksumIncrementBufferReadPointer
	RotateBuffer
	SetReadPtr 0xf350
	ReadBufferByte
	Scramble
	RotateBuffer
	ReadBufferByte
	Scramble
	RotateBuffer
	HaltAndFinalize
