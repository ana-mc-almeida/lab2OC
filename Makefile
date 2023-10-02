CC = gcc
CFLAGS=-Wall -Wextra
TARGET=SimpleCache
TARGETL1 = L1Cache

all:
	$(CC) $(CFLAGS) SimpleProgram.c SimpleCache.c -o $(TARGET)
	$(CC) $(CFLAGS) SimpleProgram.c task4-1/L1Cache.c -o $(TARGETL1)

clean:
	rm $(TARGET)