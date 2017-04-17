TARGET= flash
LIBS= -l hidapi
INCLUDE= -I /usr/local/include/hidapi/ -I ./ -I ../firmware/svaroskey/common/
CFLAGS= -g -Wall -std=c99
CC= gcc

.PHONY: default all clean

default: $(TARGET)
all: default

SRC = $(wildcard *.c)
HEADERS = $(wildcard *.h)

#SRC = 
#HEADER =

OBJECTS = $(patsubst %.c, %.o, $(SRC))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) $(INCLUDE) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
