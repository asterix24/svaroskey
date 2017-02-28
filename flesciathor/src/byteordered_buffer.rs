extern crate byteorder;

use std::io::{Error, Read, Write};
use std::marker::PhantomData;

use self::byteorder::{LittleEndian, ReadBytesExt, WriteBytesExt};


pub type ByteOrder = LittleEndian;
pub type FlashBuffer<W> = ByteOrderedBuffer<W, ByteOrder>;


#[derive(Debug)]
pub struct ByteOrderedBuffer<W, B: byteorder::ByteOrder> {
    pub inner: W,
    _marker: PhantomData<B>,
}

impl<T, B: byteorder::ByteOrder> ByteOrderedBuffer<T, B> {
    pub fn new(inner: T) -> ByteOrderedBuffer<T, B> {
        ByteOrderedBuffer {
            inner: inner,
            _marker: PhantomData,
        }
    }
}

impl<T: Write, B: byteorder::ByteOrder> ByteOrderedBuffer<T, B> {
    pub fn write_u8(&mut self, n: u8) -> Result<(), Error> {
        self.inner.write_u8(n)
    }
    pub fn write_i8(&mut self, n: i8) -> Result<(), Error> {
        self.inner.write_i8(n)
    }
    pub fn write_u16(&mut self, n: u16) -> Result<(), Error> {
        self.inner.write_u16::<B>(n)
    }
    pub fn write_i16(&mut self, n: i16) -> Result<(), Error> {
        self.inner.write_i16::<B>(n)
    }
    pub fn write_u32(&mut self, n: u32) -> Result<(), Error> {
        self.inner.write_u32::<B>(n)
    }
    pub fn write_i32(&mut self, n: i32) -> Result<(), Error> {
        self.inner.write_i32::<B>(n)
    }
    pub fn write_u64(&mut self, n: u64) -> Result<(), Error> {
        self.inner.write_u64::<B>(n)
    }
    pub fn write_i64(&mut self, n: i64) -> Result<(), Error> {
        self.inner.write_i64::<B>(n)
    }
    pub fn write_uint(&mut self, n: u64, nbytes: usize) -> Result<(), Error> {
        self.inner.write_uint::<B>(n, nbytes)
    }
    pub fn write_int(&mut self, n: i64, nbytes: usize) -> Result<(), Error> {
        self.inner.write_int::<B>(n, nbytes)
    }
    pub fn write_f32(&mut self, n: f32) -> Result<(), Error> {
        self.inner.write_f32::<B>(n)
    }
    pub fn write_f64(&mut self, n: f64) -> Result<(), Error> {
        self.inner.write_f64::<B>(n)
    }
}

impl<R: Read, B: byteorder::ByteOrder> ByteOrderedBuffer<R, B> {
    pub fn read_u8(&mut self) -> Result<u8, Error> {
        self.inner.read_u8()
    }
    pub fn read_i8(&mut self) -> Result<i8, Error> {
        self.inner.read_i8()
    }
    pub fn read_u16(&mut self) -> Result<u16, Error> {
        self.inner.read_u16::<B>()
    }
    pub fn read_i16(&mut self) -> Result<i16, Error> {
        self.inner.read_i16::<B>()
    }
    pub fn read_u32(&mut self) -> Result<u32, Error> {
        self.inner.read_u32::<B>()
    }
    pub fn read_i32(&mut self) -> Result<i32, Error> {
        self.inner.read_i32::<B>()
    }
    pub fn read_u64(&mut self) -> Result<u64, Error> {
        self.inner.read_u64::<B>()
    }
    pub fn read_i64(&mut self) -> Result<i64, Error> {
        self.inner.read_i64::<B>()
    }
    pub fn read_uint(&mut self, nbytes: usize) -> Result<u64, Error> {
        self.inner.read_uint::<B>(nbytes)
    }
    pub fn read_int(&mut self, nbytes: usize) -> Result<i64, Error> {
        self.inner.read_int::<B>(nbytes)
    }
    pub fn read_f32(&mut self) -> Result<f32, Error> {
        self.inner.read_f32::<B>()
    }
    pub fn read_f64(&mut self) -> Result<f64, Error> {
        self.inner.read_f64::<B>()
    }
}

impl<T: Write, B: byteorder::ByteOrder> Write for ByteOrderedBuffer<T, B> {
    fn write(&mut self, buf: &[u8]) -> Result<usize, Error> {
        self.inner.write(buf)
    }

    fn flush(&mut self) -> Result<(), Error> {
        self.inner.flush()
    }
}

impl<R: Read, B: byteorder::ByteOrder> Read for ByteOrderedBuffer<R, B> {
    fn read(&mut self, buf: &mut [u8]) -> Result<usize, Error> {
        self.inner.read(buf)
    }
}
