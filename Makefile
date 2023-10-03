CC = gcc
CFLAGS=-Wall -Wextra
TARGET=SimpleCache
TARGETL1 = L1Cache
TARGETL2 = L2Cache

all:
	$(CC) $(CFLAGS) SimpleProgram.c SimpleCache.c -o $(TARGET)
	$(CC) $(CFLAGS) SimpleProgramL1.c task4-1/L1Cache.c -o $(TARGETL1)
	$(CC) $(CFLAGS) SimpleProgramL2.c task4-2/L2Cache.c -o $(TARGETL2)

clean:
	rm $(TARGET)