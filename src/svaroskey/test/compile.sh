#!/bin/bash

echo "Remember: to exit the program just press together 'a' 's' 'd'!"

gcc -std=c99 *.c *.h -I/usr/include/SDL2 -lSDL2 
