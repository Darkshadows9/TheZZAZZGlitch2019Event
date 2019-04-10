use std::path::Path;
use std::io::{Read, Write};
use std::io;
use std::fs::OpenOptions;

#[derive(PartialEq, Clone, Debug)]
pub struct Decrypter {
    // pub map: [u8; 0x200], // 0x200, vec for ease of use
    pub map: Vec<u8>,
    pub iter_outer: i32,
    pub iter_inner: i32,
    pub keygen: i32,
    pub keygen_mul: i32,
    pub keygen_add: i32,
    pub keygen_mul_inverse: i32,
}

impl Decrypter {
    const BANK_OFFSET: usize = 0x6000;
    const MAP_OFFSET: usize = Self::BANK_OFFSET + 0x567;
    const KEYGEN_OFFSET: usize = Self::BANK_OFFSET + 0x0f3;
    const KEYGEN_ADD_OFFSET: usize = Self::BANK_OFFSET + 0x0fb;
    const KEYGEN_MUL_OFFSET: usize = Self::BANK_OFFSET + 0x0f7;
    const ITER_INNER_OFFSET: usize = Self::BANK_OFFSET + 0x103;
    const ITER_OUTER_OFFSET: usize = Self::BANK_OFFSET + 0x0ff;
    const MAP_LENGTH: usize = 0x200;

    const ENTRY_POINT_FUNC: usize = 0x13a;
    const KEY_MOD_FUNC: usize = 0x10f;
    const MUL32_FUNC: usize = 0x0c4;
    const NON0_COND_FUNC: usize = 0x0a4;
    const ADD32_FUNC: usize = 0x090;
    const MOV32_FUNC: usize = 0x084;

    const RETURN_INS: u8 = 0xc9;

    /// Full decryption execution.
    pub fn run_normal(&mut self) {
        for i in 0..self.iter_outer {
            self.step();
            println!("{} of {}", i, self.iter_outer);
        }
    }

    pub fn run_reverse(&mut self) {
        let loops = 0x8000_0000 - self.iter_outer as u32;
        for i in 0..loops {
            self.inverse_step();
            println!("{} of {}", i, loops);
        }
    }

    // Individual decryption Steps. Read it to understand its power!
    #[inline(always)]
    fn step(&mut self) {
        self.step_block();
        self.keygen = self.keygen.wrapping_mul(self.keygen_mul).wrapping_add(self.keygen_add);
    }

    #[inline(always)]
    fn inverse_step(&mut self) {
        self.keygen = self.keygen.wrapping_sub(self.keygen_add).wrapping_mul(self.keygen_mul_inverse);
        self.step_block();
    }

    #[inline(always)]
    fn step_block(&mut self) {
        let bytes = self.keygen.to_le_bytes();
        let mut var = u16::from(bytes[1]);
        let var_mul = u16::from(bytes[2]);
        let var_add = u16::from(bytes[3]);
        for (_, i) in (0..self.iter_inner).zip((0..Self::MAP_LENGTH).cycle()) {
            var = (var >> 1)
                .wrapping_mul(var_mul)
                .wrapping_add(var_add);
            self.map[i] ^= var.to_le_bytes()[0];
        }
    }

    /// Create the struct from a .sav file. After which the file gets ignored.
    pub fn load<P: AsRef<Path>>(path: P) -> io::Result<Self> {
        let mut file = OpenOptions::new().read(true).write(true).open(&path)?;
        let buf = &mut Vec::new();
        file.read_to_end(buf)?;

        let map = buf[Self::MAP_OFFSET..Self::MAP_OFFSET + Self::MAP_LENGTH].to_vec();

        let iter_inner = Self::int_at(Self::ITER_INNER_OFFSET, &buf);
        let iter_outer = Self::int_at(Self::ITER_OUTER_OFFSET, &buf);
        let keygen_mul = Self::int_at(Self::KEYGEN_MUL_OFFSET, &buf);
        let keygen_add = Self::int_at(Self::KEYGEN_ADD_OFFSET, &buf);
        let keygen = Self::int_at(Self::KEYGEN_OFFSET, &buf);

        let keygen_mul_inverse = Self::eea(i64::from(keygen_mul), 0x1_0000_0000) as i32;

        Ok(Decrypter{
            iter_inner, iter_outer, keygen, keygen_add, keygen_mul, map, keygen_mul_inverse
        })
    }

    /// Inserts into a .sav file the current map and skips decrypting ingame.
    pub fn insert_into<P: AsRef<Path>>(&self, path: P) -> io::Result<()> {
        let mut file = OpenOptions::new().read(true).open(&path)?;
        let mut buf = Vec::new();
        file.read_to_end(&mut buf)?;
        // Insert current map buffer
        buf[Self::MAP_OFFSET..(Self::MAP_LENGTH + Self::MAP_OFFSET)].clone_from_slice(&self.map[..Self::MAP_LENGTH]);
        // Skip the Decryption function, when its called.
        buf[Self::ENTRY_POINT_FUNC] = Self::RETURN_INS;
        println!("{:02x?}", &buf[Self::MAP_OFFSET..Self::MAP_OFFSET+Self::MAP_LENGTH]);

        drop(file); // explicitly drop to be sure, to open it in write mode. meh
        let mut file = OpenOptions::new().write(true).truncate(true).open(&path)?;

        file.write_all(&buf)?;
        Ok(())
    }

    fn int_at(pt: usize, buf: &[u8]) -> i32 {
        i32::from_le_bytes([buf[pt], buf[pt+1], buf[pt+2], buf[pt+3]])
    }

    // Runs one interation step forwards and backwards as a stability check.
    fn _inverse_check(&mut self) -> bool {
        let copy = self.clone();
        self.step();
        self.inverse_step();
        *self == copy
    }

    //inverse of ia in modulo ib
    fn eea(ia: i64, ib: i64) -> i64 {
        let (mut a, mut b) = (ia.max(ib), ia.min(ib));
        let mut invp = 0;
        let mut inv = 1;

        while b != 0 {
            // division
            let c = a / b;
            let temp = invp - c * inv;
            invp = inv;
            inv = temp;

            // remainder
            let c = a % b;
            a = b;
            b = c;
            // println!("a:{}, b:{}, inv:{}, invp:{}", a, b, inv, invp);
        }
        assert!(a == 1);
        assert!(ia.wrapping_mul(invp) % ib == 1);

        invp
    }
}


impl std::fmt::Display for Decrypter {
    fn fmt<'a>(&self, fmt: &mut std::fmt::Formatter<'a>) -> std::result::Result<(), std::fmt::Error> {
        writeln!(fmt, "Decrypter Technologies LLC")?;
        writeln!(fmt, "iter_inner: 0x{:08x}", self.iter_inner)?;
        writeln!(fmt, "iter_outer: 0x{:08x}", self.iter_outer)?;
        writeln!(fmt, "keygen_mul: 0x{:08x}", self.keygen_mul)?;
        writeln!(fmt, "keygen_add: 0x{:08x}", self.keygen_add)?;
        writeln!(fmt, "keygen: 0x{:08x}", self.keygen)?;
        Ok(())
    }
}