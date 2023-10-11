CC = gcc
CFLAGS=-Wall -Wextra
TARGET=SimpleCache
TARGETL1 = L1Cache
TARGETL2 = L2Cache
TARGET2WL2 = 2WL2Cache
TARGET_TESTSL1 = testsL1
TARGET_TESTSL2 = testsL2
TARGET_TESTS2WL2 = tests2WL2

all:
	$(CC) $(CFLAGS) SimpleProgram.c SimpleCache.c -o $(TARGET)
	$(CC) $(CFLAGS) task4-1/SimpleProgramL1.c task4-1/L1Cache.c -o $(TARGETL1)
	$(CC) $(CFLAGS) task4-2/SimpleProgramL2.c task4-2/L2Cache.c -o $(TARGETL2)
	$(CC) $(CFLAGS) task4-3/SimpleProgram2wayL2.c task4-3/2wayL2Cache.c -o $(TARGET2L2)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-1/L1Cache.c -o $(TARGET_TESTSL1)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-2/L2Cache.c -o $(TARGET_TESTSL2)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-3/2wayL2Cache.c -o $(TARGET_TESTS2WL2)

clean:
	rm $(TARGET)