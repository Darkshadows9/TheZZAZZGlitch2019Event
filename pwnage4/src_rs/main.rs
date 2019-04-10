
// meh i cant think anymore



enum Instructions {
    WriteWord(u16),
    WriteByte(u8),
    CopyByte,
    Scramble,
    RotateBuffer,
    WriteLong(u32),
    UpdateChecksum,
    UpdateChecksum2,
    ReadByte,
    Djnz(usize, u8),
}

#[derive(PartialEq, Clone)]
struct State {
    sram: Vec<u8>, // 02:A000 to BFFF
}

// where the instructions write to, pointers
const WRITE_WORD_PTR: usize = 0xAEF5; // 2b
const WRITE_LONG_PTR: usize = 0xAFE5; // 4b
const WRITE_BYTE_PTR: usize = 0xAF0B; // 1b
// dunno
const ADDRESS_BUFFER1: usize = 0xAF1B; // 2b
const COPY_BYTE_SIDE_EFFECT: usize = 0xAF31; // 2b
const COPY_BYTE_PTR: usize = 0xAF31; // 1b


impl Instructions {

    fn run(&self, mut state: State) -> State {
        use Instructions::*;
        match self {
            WriteWord(imm) => {
                let bytes = imm.to_le_bytes();
                state.sram[WRITE_WORD_PTR] = bytes[0];
                state.sram[WRITE_WORD_PTR+1] = bytes[1];
            }
            WriteByte(imm) => {
                state.sram[WRITE_BYTE_PTR] = *imm;
            }
            CopyByte => { // TODO

            }
            Scramble => {

            }
            RotateBuffer => {

            }
            WriteLong(imm) => {
                let bytes = imm.to_le_bytes();
                state.sram[WRITE_LONG_PTR] = bytes[0];
                state.sram[WRITE_LONG_PTR+1] = bytes[1];
                state.sram[WRITE_LONG_PTR+2] = bytes[2];
                state.sram[WRITE_LONG_PTR+3] = bytes[3];
            }
            UpdateChecksum => {

            }
            UpdateChecksum2 => {

            }
            ReadByte => {

            }
            Djnz(jump_to, imm) => {

            }
        }
        state
    }
}


struct SaveMachine {
    program: Vec<Instructions>,
    de: usize, //16bit please // ip

    buffer_address: u16,

}

impl SaveMachine {

    fn new() -> Self {
        let program: Vec<Instructions> = vec![

        ];
        unimplemented!()
    }

}




fn main() {



    println!("Hello, world!");
}
