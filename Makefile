CC = gcc
CFLAGS=-Wall -Wextra
TARGET=SimpleCache
TARGETL1_1 = L1Cache_1
TARGETL2_1 = L2Cache_1
TARGET2WL2_1 = 2WL2Cache_1
TARGETL1_2 = L1Cache_2
TARGETL2_2 = L2Cache_2
TARGET2WL2_2 = 2WL2Cache_2
TARGETL1_3 = L1Cache_3
TARGETL2_3 = L2Cache_3
TARGET2WL2_3 = 2WL2Cache_3
TARGET_TESTSL1 = testsL1
TARGET_TESTSL2 = testsL2
TARGET_TESTS2WL2 = tests2WL2

all:
	$(CC) $(CFLAGS) SimpleProgram.c SimpleCache.c -o $(TARGET)
	$(CC) $(CFLAGS) SimpleProgram.c task4-1/L1Cache.c -o $(TARGETL1_1)
	$(CC) $(CFLAGS) SimpleProgram.c task4-2/L2Cache.c -o $(TARGETL2_1)
	$(CC) $(CFLAGS) SimpleProgram.c task4-3/2wayL2Cache.c -o $(TARGET2WL2_1)
	$(CC) $(CFLAGS) SimpleProgram2.c task4-1/L1Cache.c -o $(TARGETL1_2)
	$(CC) $(CFLAGS) SimpleProgram2.c task4-2/L2Cache.c -o $(TARGETL2_2)
	$(CC) $(CFLAGS) SimpleProgram2.c task4-3/2wayL2Cache.c -o $(TARGET2WL2_2)
	$(CC) $(CFLAGS) SimpleProgram3.c task4-1/L1Cache.c -o $(TARGETL1_3)
	$(CC) $(CFLAGS) SimpleProgram3.c task4-2/L2Cache.c -o $(TARGETL2_3)
	$(CC) $(CFLAGS) SimpleProgram3.c task4-3/2wayL2Cache.c -o $(TARGET2WL2_3)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-1/L1Cache.c -o $(TARGET_TESTSL1)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-2/L2Cache.c -o $(TARGET_TESTSL2)
	$(CC) $(CFLAGS) tests_alunos/SimpleProgram.c task4-3/2wayL2Cache.c -o $(TARGET_TESTS2WL2)

clean:
	rm $(TARGET)
	rm $(TARGETL1_1)
	rm $(TARGETL2_1)
	rm $(TARGET2WL2_1)
	rm $(TARGETL1_2)
	rm $(TARGETL2_2)
	rm $(TARGET2WL2_2)
	rm $(TARGETL1_3)
	rm $(TARGETL2_3)
	rm $(TARGET2WL2_3)
	rm $(TARGET_TESTSL1)
	rm $(TARGET_TESTSL2)
	rm $(TARGET_TESTS2WL2)