extern crate hidapi;

use std::fs::File;
use std::io::{Cursor, Read, Write};

use self::hidapi::{HidApi, HidDevice, HidDeviceInfo};

use errors::FlashResult;
use byteordered_buffer::FlashBuffer;


include!(concat!(env!("OUT_DIR"), "/vendor.rs"));


const INIT_BOOT: u8 = 0x00;

const MAX_SIZE: usize = 16;


trait Flasher {
    fn send(&mut self, u8, &[u8]) -> FlashResult<Vec<u8>>;
}


impl<'a> Flasher for HidDevice<'a> {
    fn send(&mut self, ty: u8, body: &[u8]) -> FlashResult<Vec<u8>> {
        let data = {
            let mut tmp = body.to_vec();
            tmp.insert(0, ty);
            tmp
        };

        self.send_feature_report(&data)?;

        let mut buf = vec![0; MAX_SIZE];
        buf[0] = ty;

        self.get_feature_report(&mut buf)?;

        Ok(buf)
    }
}


pub fn search_devices(api: &HidApi) -> Vec<HidDeviceInfo> {
    api.devices().into_iter().filter(|d| d.vendor_id == VENDOR_ID).collect()
}


pub fn flash(api: &HidApi, devinfo: &HidDeviceInfo, firmware: &str) -> FlashResult<()> {
    let mut firmware = {
        let mut tmp = Vec::new();
        File::open(firmware)?.read_to_end(&mut tmp)?;
        tmp
    };

    let mut dev = api.open(devinfo.vendor_id, devinfo.product_id)?;

    _flash(&mut dev, &mut firmware)
}



fn _flash(dev: &mut HidDevice, firmware: &[u8]) -> FlashResult<()> {
    _init_boot(dev, firmware)
}


fn _init_boot(dev: &mut HidDevice, firmware: &[u8]) -> FlashResult<()> {
    let crc = firmware.iter().fold(0, |acc, x| acc | x);

    let mut buf = FlashBuffer::new(Cursor::new(vec![0; 16]));

    buf.write_u8(INIT_BOOT)?;
    buf.write_all("BOOT".as_bytes())?;
    buf.write_u64(firmware.len() as u64)?;
    buf.write_u64(crc as u64)?;

    dev.send_feature_report(buf.inner.get_ref())?;

    Ok(())
}


#[cfg(test)]
mod tests {
    use super::*;

    pub struct TestFlasher {
        responses: Vec<Vec<u8>>,
        requests: Vec<Vec<u8>>,
        i: usize,
    }

    impl TestFlasher {
        pub fn new(resps: Vec<Vec<u8>>) -> TestFlasher {
            TestFlasher {
                responses: resps,
                requests: Vec::new(),
                i: 0,
            }
        }
    }

    impl Flasher for TestFlasher {
        fn send(&mut self, ty: u8, body: &[u8]) -> FlashResult<Vec<u8>> {
            let data = {
                let mut tmp = body.to_vec();
                tmp.insert(0, ty);
                tmp
            };

            self.requests.push(data);

            self.i += 1;

            Ok(self.responses[self.i - 1].clone())
        }
    }
}
