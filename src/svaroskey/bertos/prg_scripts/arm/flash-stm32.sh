#!/bin/bash

echo "Flash $IMAGE_FILE on Nucleo Board.. on Port $PROGRAMMER_PORT"
echo
#st-flash write $IMAGE_FILE 0x8000000
echo ""stm32flash -e 100 -w $IMAGE_FILE -v $PROGRAMMER_PORT -b 115200""
stm32flash  -b 115200 -e 100 -w $IMAGE_FILE -v $PROGRAMMER_PORT
echo
echo

