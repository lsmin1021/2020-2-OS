CC = gcc
CFLAGS = -W -Wall
TARGET = testlib
OBJECTS = bitmap.o debug.o hash.o hex_dump.o list.o main.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJECTS) $(TARGET)
