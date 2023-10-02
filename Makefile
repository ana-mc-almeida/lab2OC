CC = gcc
CFLAGS=-Wall -Wextra
TARGET=SimpleCache

all:
	$(CC) $(CFLAGS) SimpleProgram.c task4-1/L1Cache.c -o $(TARGET)

clean:
	rm $(TARGET)