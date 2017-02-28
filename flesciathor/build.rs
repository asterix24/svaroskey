use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader, Write};
use std::path::Path;

fn main() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("vendor.rs");
    let mut f = File::create(&dest_path).unwrap();

    let cfg_usbkbd = Path::new("..")
        .join("firmware")
        .join("svaroskey")
        .join("svaroskey")
        .join("cfg")
        .join("cfg_usbkbd.h");

    let cfg_usbkbd = File::open(cfg_usbkbd).expect("unable to open cfg_usbkbd.h");
    let reader = BufReader::new(cfg_usbkbd);

    let mut vendor_id: Option<u16> = None;

    for line in reader.lines() {
        let line = line.unwrap();
    
        if line.starts_with("#define USB_KEYBOARD_VENDOR_ID") {

            let v = line.split_whitespace().nth(2).expect("a value for VENDOR_ID");
            
            let v = if v.starts_with("0x") || v.starts_with("0X") {
                u16::from_str_radix(&v[2..], 16).expect("vendor id")
            } else {
                line.parse().expect("vendor id")
            };

            vendor_id = Some(v);

            break;
        }
    }

    let vendor_id = vendor_id.expect("no vendor id found!");

    f.write_all(format!("
        pub const VENDOR_ID: u16 = {};
    ", vendor_id).into_bytes().as_slice())
        .unwrap();
}