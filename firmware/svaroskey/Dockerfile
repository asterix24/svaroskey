FROM ubuntu:xenial

RUN dpkg --add-architecture i386
RUN apt-get update
RUN apt-get install -y curl bzip2 tar make libc6:i386
RUN curl -L "http://www.codesourcery.com/sgpp/lite/arm/portal/package5353/public/arm-none-eabi/arm-2009q3-68-arm-none-eabi-i686-pc-linux-gnu.tar.bz2" | tar -C /opt -jxf -

ENV PATH=$PATH:/opt/arm-2009q3/bin

WORKDIR /build
VOLUME ["/build"]

CMD ["make"]
