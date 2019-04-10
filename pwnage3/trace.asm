ITER_INNER  EQU a103
ITER_OUTER  EQU a0ff
KEYGEN      EQU a0f3
KEYGEN_MUL  EQU a0f7
KEYGEN_ADD  EQU a0fb
MAP         EQU a567

entryPoint:
  03:a13a                  ld   hl,a107
  03:a13d                  ld   de,ITER_INNER
  03:a140                  call copy32Bits
  03:a143                  ld   hl,a0f4
  03:a146                  ld   de,a10b
  03:a149                  ldi  a,(hl)
  03:a14a                  ld   (de),a
  03:a14b                  inc  de
  03:a14c                  xor  a
  03:a14d                  ld   (de),a
  03:a14e                  inc  de
  03:a14f                  ldi  a,(hl)
  03:a150                  ld   (de),a
  03:a151                  inc  de
  03:a152                  ld   a,(hl)
  03:a153                  ld   (de),a
  03:a154                  ld   hl,MAP
  03:a157                  ld   bc,NULL
.a15a:
  03:a15a                  push hl
  03:a15b                  push bc
  03:a15c                  call wrapAround
  03:a15f                  pop  bc
  03:a160                  pop  hl
  03:a161                  xor  (hl)
  03:a162                  ldi  (hl),a
  03:a163                  inc  bc
  03:a164                  ld   a,b
  03:a165                  cp   a,02
  03:a167                  jr   nz,a16f
  03:a169                  ld   bc,NULL
  03:a16c                  ld   hl,MAP
.a16f:
  03:a16f                  push hl
  03:a170                  ld   hl,a107
  03:a173                  call nonZeroConditional
  03:a176                  pop  hl
  03:a177                  jr   nz,a15a
  03:a179                  ld   hl,KEYGEN
  03:a17c                  ld   de,KEYGEN_MUL
  03:a17f                  call multiply32Bits
  03:a182                  ld   hl,KEYGEN
  03:a185                  ld   de,KEYGEN_ADD
  03:a188                  call add32Bits
  03:a18b                  ld   hl,ITER_OUTER
  03:a18e                  call nonZeroConditional
  03:a191                  jr   nz,a13a
  03:a193                  ret

copy32Bits: (03:a084)
  03:a084                  ld   a,(de)
  03:a085                  ldi  (hl),a
  03:a086                  inc  de
  03:a087                  ld   a,(de)
  03:a088                  ldi  (hl),a
  03:a089                  inc  de
  03:a08a                  ld   a,(de)
  03:a08b                  ldi  (hl),a
  03:a08c                  inc  de
  03:a08d                  ld   a,(de)
  03:a08e                  ld   (hl),a
  03:a08f                  ret

add32Bits: (03:a090)
  03:add32Bits             ld   a,(de)
  03:a091                  add  (hl)
  03:a092                  ldi  (hl),a
  03:a093                  inc  de
  03:a094                  ld   a,(de)
  03:a095                  adc  (hl)
  03:a096                  ldi  (hl),a
  03:a097                  inc  de
  03:a098                  ld   a,(de)
  03:a099                  adc  (hl)
  03:a09a                  ldi  (hl),a
  03:a09b                  inc  de
  03:a09c                  ld   a,(de)
  03:a09d                  adc  (hl)
  03:a09e                  ld   (hl),a
  03:a09f                  ret

nonZeroConditional: (03:a0a4)
  03:a0a4                  push hl
  03:a0a5                  ld   de,a0a0
  03:a0a8                  call add32Bits
  03:a0ab                  pop  hl
  03:a0ac                  ldi  a,(hl)
  03:a0ad                  and  a
  03:a0ae                  ret  nz
  03:a0af                  ldi  a,(hl)
  03:a0b0                  and  a
  03:a0b1                  ret  nz
  03:a0b2                  ldi  a,(hl)
  03:a0b3                  and  a
  03:a0b4                  ret  nz
  03:a0b5                  ldi  a,(hl)
  03:a0b6                  and  a
  03:a0b7                  ret

multiply32Bits: (03:a0c4)
  03:a0c4                  push hl
  03:a0c5                  push hl
  03:a0c6                  push de
  03:a0c7                  ld   hl,a0b8
  03:a0ca                  call copy32Bits
  03:a0cd                  pop  de
  03:a0ce                  pop  hl
  03:a0cf                  push hl
  03:a0d0                  ld   hl,a0bc
  03:a0d3                  ld   de,a0c0
  03:a0d6                  call copy32Bits
  03:a0d9                  pop  de
.a0da:
  03:a0da                  push de
  03:a0db                  ld   hl,a0bc
  03:a0de                  call add32Bits
  03:a0e1                  pop  de
  03:a0e2                  push de
  03:a0e3                  ld   hl,a0b8
  03:a0e6                  call nonZeroConditional
  03:a0e9                  pop  de
  03:a0ea                  jr   nz,a0da
  03:a0ec                  pop  hl
  03:a0ed                  ld   de,a0bc
  03:a0f0                  jp   copy32Bits

wrapAround: (03:a10f)
  03:a10f                  ld   hl,a10b
  03:a112                  ldi  a,(hl)
  03:a113                  ld   h,(hl)
  03:a114                  ld   l,a
  03:a115                  and  a
  03:a116                  srl  h
  03:a118                  rr   l
  03:a11a                  ld   d,h
  03:a11b                  ld   e,l
  03:a11c                  ld   hl,NULL
  03:a11f                  ld   a,(a10d)
  03:a122                  ld   c,a
  03:a123                  and  a
  03:a124                  jr   z,a12a
.a126:
  03:a126                  add  hl,de
  03:a127                  dec  c
  03:a128                  jr   nz,a126
.a12a:
  03:a12a                  ld   a,(a10e)
  03:a12d                  ld   c,a
  03:a12e                  ld   b,00
  03:a130                  add  hl,bc
  03:a131                  ld   a,h
  03:a132                  ld   (a10c),a
  03:a135                  ld   a,l
  03:a136                  ld   (a10b),a
  03:a139                  ret