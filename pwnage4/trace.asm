sp	function	code

AE18:	1898		ld	a,(de)
AE1A:	106A		inc	de
AE1C:	3E3D		add	a
AE1E:	08F1		pop	bc
AE20:	0000		//constant for ^
AE22:	0D8E		ld	c,a
AE24:	0831		pop	hl
AE26:	AE2C		//constant for ^
AE28:	1D17		add	hl,bc
AE2A:	1C85		ldi	a,(hl)
					ld	h,(hl)
					ld	l,a
AE2C:	1708		ld	sp,hl

AE2E:	AEF3
AE30:	AF09
AE32:	AF19
AE34:	AE4A
AE36:	AF3B
AE38:	AF85
AE3A:	AFE3
AE3C:	B005
AE3E:	B013
AE40:	0000
AE42:	B033
AE44:	B07D
AE46:	B045
AE48:	B069

AE4A:

AEF3:	0831		pop	hl
AEF5:	ADAE		//constant for ^
AEF7:	1898		ld	a,(de)
AEF9:	2250		ldi	(hl),a
AEFB:	106A		inc	de
AEFD:	1898		ld	a,(de)
AEFF:	2250		ldi	(hl),a
AF01:	106A		inc	de
AF03:	0831		pop	hl
AF05:	AE18		//constant for ^
AF07:	1708		ld	sp,hl

AF09:	0831		pop	hl
AF0B:	ADB0		//constant for ^
AF0D:	1898		ld	a,(de)
AF0F:	106A		inc	de
AF11:	2250		ldi	(hl),a
AF13:	0831		pop	hl
AF15:	AE18		//constant for ^
AF17:	1708		ld	sp,hl

AF19:	0831		pop	hl
AF1B:	ADAE		//constant for ^
AF1D:	1C85		ldi	a,(hl)
					ld	h,(hl)
					ld	l,a
AF1F:	ADBA		ldi	a,(hl)
AF21:	4404		ld	b,h
AF23:	18DC		ld	c,l
AF25:	0831		pop	hl
AF27:	ADAE		//constant for ^
AF29:	ADBE		ld	(hl),c
AF2B:	1447		inc	hl
AF2D:	1FEE		ld	(hl),b
AF2F:	0831		pop	hl
AF31:	C800		//constant for ^
AF33:	2250		ldi	(hl),a
AF35:	0831		pop	hl
AF37:	AE18		//constant for ^
AF39:	1708		ld	sp,hl

AF3B:	0831		pop	hl
AF3D:	ADB1		//constant for ^
AF41:	ADC0		ld	b,(hl)
AF43:	ADBA		ldi	a,(hl)
AF45:	ADBA		ldi	a,(hl)
AF47:	ADBA		ldi	a,(hl)
AF49:	ADBC		ldd	a,(hl)
AF4B:	0933		xor	b
AF4D:	1489		ld	b,a
AF4F:	ADBC		ldd	a,(hl)
AF51:	ADBC		ldd	a,(hl)
AF53:	1447		inc	hl
AF55:	0933		xor	b
AF57:	2250		ldi	(hl),a
AF59:	1489		ld	b,a
AF5B:	ADBC		ldd	a,(hl)
AF5D:	1447		inc	hl
AF5F:	ADC2		add	b
AF61:	2250		ldi	(hl),a
AF63:	ADC4		srl	a
AF65:	1489		ld	b,a
AF67:	ADBC		ldd	a,(hl)
AF69:	ADC2		add	b
AF6B:	1489		ld	b,a
AF6D:	ADBC		ldd	a,(hl)
AF6F:	ADBA		ldi	a,(hl)
AF71:	0933		xor	b
AF73:	1447		inc	hl
AF75:	2250		ldi	(hl),a
AF77:	0831		pop	hl
AF79:	C800		//constant for ^
AF7B:	ADC7		xor (hl)
AF7D:	2250		ldi	(hl),a
AF7F:	0831		pop	hl
AF81:	AE18		//constant for ^
AF83:	1708		ld	sp,hl

AF85:	0831		pop	hl
AF87:	ADB8		//constant for ^
AF89:	ADBC		ldd	a,(hl)
AF8B:	37C2		inc	a
AF8D:	0831		pop	hl
AF8F:	07FC		//constant for ^
AF91:	2DE0		or	(hl)
AF93:	08F1		pop	bc
AF95:	C000		//constant for ^
AF97:	0933		xor	b
AF99:	0831		pop	hl
AF9B:	ADB8		//constant for ^
AF9D:	2250		ldi	(hl),a
AF9F:	0394		and	a
AFA1:	ADC9		ret	z
		ADCA		pop	hl //AEDB
AFA3:	AEDB		ld	hl,9A12 //Ignore if not ret z at ADC9
		AEDE		ld	b,C0
		AEE0		ld	a,(ADB9)
		AEE3		inc	a
		AEE4		and	a,03
		AEE6		ld	(ADB9),a
		AEE9		add	b
		AEEA		ld	b,a
		AEEB		ld	a,(ff00+41)
		AEED		and	a,03
		AEEF		jr	nz,AEEB
		AEE1		ld	(hl),b
AFA5:	0831		pop	hl
AFA7:	ADB6		//constant for ^
AFA9:	18D0		ld	a,e
AFAB:	2250		ldi	(hl),a
AFAD:	3351		ld	(hl),d
AFAF:	0831		pop	hl
AFB1:	C800		//constant for ^
AFB3:	ADBA		ldi	a,(hl)
AFB5:	0831		pop	hl
AFB7:	ADB5		//constant for ^
AFB9:	2250		ldi	(hl),a
AFBB:	09A2		pop	bc
		09A3		pop	de
		09A4		pop	hl
		09A5		pop	af
AFBD:	01B0		//constant bc for ^
AFBF:	C800		//constant de for ^
AFC1:	C801		//constant hl for ^
AFC3:	FF00		//constant af for ^
AFC5:	3026 CopyBytes:	inc	b //built-in function. Copies bc bytes from (hl) to (de)
		2027		inc	c
		2028		jr	302D
		302A		ldi	a,(hl)
		302B		ld	(de),a
		302C		inc	de
		302D		dec	c
		302E		jr	nz,302A
		3030		dec	b
		3031		jr	nz,302A
AFC7:	0831		pop	hl
AFC9:	ADB5		//constant for ^
AFCB:	ADBA		ldi	a,(hl)
AFCD:	0831		pop	hl
AFCF:	C9AF		//constant for ^
AFD1:	2250		ldi	(hl),a
AFD3:	0831		pop	hl
AFD5:	ADB6		//constant for ^
AFD7:	ADBA		ldi	a,(hl)
AFD9:	5E0C		ld	d,(hl)
AFDB:	1FA5		ld	e,a
AFDD:	0831		pop	hl
AFDF:	AE18		//constant for ^
AFE1:	1708		ld	sp,hl

AFE3:	0831		pop	hl
AFE5:	ADB1		//constant for ^
AFE7:	1898		ld	a,(de)
AFE9:	2250		ldi	(hl),a
AFEB:	106A		inc	de
AFED:	1898		ld	a,(de)
AFEF:	2250		ldi	(hl),a
AFF1:	106A		inc	de
AFF3:	1898		ld	a,(de)
AFF5:	2250		ldi	(hl),a
AFF7:	106A		inc	de
AFF9:	1898		ld	a,(de)
AFFB:	2250		ldi	(hl),a
AFFD:	106A		inc	de
AFFF:	0831		pop	hl
B001:	AE18		//constant for ^
B003:	1708		ld	sp,hl

B005:	09A4		pop hl
					pop af
B007:	ADCC		constant hl for ^
B009:	8600		constant af for ^
B00B:	2250		ldi	(hl),a
B00D:	0831		pop	hl
B00F:	B01B		//constant for ^
B011:	1708		ld	sp,hl

B013:	09A4		pop	hl
		09A5		pop	af
B015:	ADCC		//constant hl for ^
B017:	AE00		//constant af for ^
B019:	2250		ldi	(hl),a
B01B:	0831		pop	hl
B01D:	ADB0		//constant for ^
B01F:	ADBA		ldi	a,(hl)
B021:	0831		pop	hl
B023:	C800		//constant for ^
B025:	ADCC		add	(hl)
B027:	0831		pop	hl
B029:	ADB0		//constant for ^
B02B:	2250		ldi	(hl),a
B02D:	0831		pop	hl
B02F:	AE18		//constant for ^
B031:	1708		ld	sp,hl

B045:	0831		pop	hl
B047:	ADB0		//constant for ^
B049:	ADC0		ld	b,(hl)
B04B:	0831		pop	hl
B04D:	ADAE		//constant for ^
B04F:	1C85		ldi	a,(hl)
					ld	h,(hl)
					ld	l,a
B051:	1FEE		ld	(hl),b
B053:	1447		inc	hl
B055:	4404		ld	b,h
B057:	18DC		ld	c,l
B059:	0831		pop	hl
B05B:	ADAE		//constant for ^
B05D:	ADBE		ld	(hl),c
B05F:	1447		inc	hl
B061:	1FEE		ld	(hl),b
B063:	0831		pop	hl
B065:	AE18		//constant for ^
B067:	1708		ld	sp,hl

B07D:	1898		ld	a,(de)
B07F:	0D8E		ld	c,a
B081:	106A		inc	de
B083:	1898		ld	a,(de)
B085:	1489		ld	b,a
B087:	106A		inc	de
B089:	1898		ld	a,(de)
B08B:	106A		inc	de
B08D:	0831		pop	hl
B08F:	AE18		//constant for ^
B091:	0394		and	a
B093:	ADC9		ret	z
		ADCA		pop	hl //1708
B095:	1708		ld	sp,hl //ignore if not ret z at ADC9

B097:	2EC9		dec	a
B099:	1380		dec	de
B09B:	4128		ld	(de),a
B09D:	106A		inc	de
B09F:	0831		pop	hl
B0A1:	AE18		//constant for ^
B0A3:	ADC9		ret	z
		ADCA		pop	hl //1708
B0A5:	1708		ld	sp,hl //ignore if not ret z at ADC9

BOA7:	4D6A		ld	d,b
BOA9:	2CAD		ld	a,c
BOAB:	1FA5		ld	e,a
BOAD:	0831		pop	hl
BOAF:	AE18		//constant for ^
BOB1:	1708		ld	sp,hl
