extern crate hidapi;

use std::{convert, fmt, io, error};


pub type FlashResult<O> = Result<O, FlashError>;


#[derive(Debug)]
pub enum FlashError {
    IoErr(io::Error),
    HidErr(hidapi::HidError),
}

impl convert::From<io::Error> for FlashError {
    fn from(err: io::Error) -> FlashError {
        FlashError::IoErr(err)
    }
}

impl convert::From<hidapi::HidError> for FlashError {
    fn from(err: hidapi::HidError) -> FlashError {
        FlashError::HidErr(err)
    }
}

impl fmt::Display for FlashError {
    fn fmt(&self, f: &mut fmt::Formatter) -> Result<(), fmt::Error> {
        match self {
            &FlashError::IoErr(ref e) => e.fmt(f),
            &FlashError::HidErr(ref e) => e.fmt(f),
        }
    }
}

impl error::Error for FlashError {
    fn description(&self) -> &str {
        match self {
            &FlashError::IoErr(ref e) => e.description(),
            &FlashError::HidErr(ref e) => e,
        }
    }
}
