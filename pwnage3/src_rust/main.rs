use std::io;

mod lib;
use lib::Decrypter;

fn main() -> io::Result<()> {
    let mut dec = Decrypter::load("fools.sav")?;

    dec.run_reverse();

    dec.insert_into("fools.sav")?;
    Ok(())
}
