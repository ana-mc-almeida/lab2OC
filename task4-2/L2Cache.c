#include "L2Cache.h"

uint8_t L1Cache[L1_SIZE];
uint8_t L2Cache[L2_SIZE];
uint8_t DRAM[DRAM_SIZE];
uint32_t time;
CacheL1 SimpleCache1;
CacheL2 SimpleCache2;

/**************** Time Manipulation ***************/
void resetTime() { time = 0; }

uint32_t getTime() { return time; }

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t address, uint8_t *data, uint32_t mode) {

  if (address >= DRAM_SIZE - WORD_SIZE + 1)
    exit(-1);

  if (mode == MODE_READ) {
    memcpy(data, &(DRAM[address]), BLOCK_SIZE);
    time += DRAM_READ_TIME;
  }

  if (mode == MODE_WRITE) {
    memcpy(&(DRAM[address]), data, BLOCK_SIZE);
    time += DRAM_WRITE_TIME;
  }
}

/*********************** L2 cache *************************/

void accessL2(uint32_t address, uint8_t *data, uint32_t mode) {
  uint32_t index, Tag, MemAddress, offset;
  uint8_t TempBlock[BLOCK_SIZE];

  /* init cache */
  if (SimpleCache2.init == 0) {  
    for (int i = 0; i < L2_SIZE/BLOCK_SIZE; i++)
      SimpleCache2.line[i].Valid = 0;
    SimpleCache2.init = 1;
  }
  offset = address % BLOCK_SIZE;
  index = (address/BLOCK_SIZE) % (L2_SIZE/BLOCK_SIZE);
  Tag = address/L2_SIZE;

  CacheLine *Line = &SimpleCache2.line[index];

  MemAddress = address - offset; // address of the block in memory

  /* access Cache*/

  if (!Line->Valid || Line->Tag != Tag) {         // if block not present - miss
    accessDRAM(MemAddress, TempBlock, MODE_READ); // get new block from DRAM

    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      MemAddress = (Line->Tag * L2_SIZE) | (index * BLOCK_SIZE); // get address of the block in memory
      accessDRAM(MemAddress, &(L2Cache[index * BLOCK_SIZE]),
                 MODE_WRITE); // then write back old block
    }

    memcpy(&(L2Cache[index * BLOCK_SIZE]), TempBlock,
           BLOCK_SIZE); // copy new block to cache line
    Line->Valid = 1;
    Line->Tag = Tag;
    Line->Dirty = 0;
  } // if miss, then replaced with the correct block

  if (mode == MODE_READ) {    // read data from cache line
    memcpy(data, &(L2Cache[index * BLOCK_SIZE]), BLOCK_SIZE);
    time += L2_READ_TIME;
  }

  if (mode == MODE_WRITE) { // write data from cache line
    memcpy(&(L2Cache[index * BLOCK_SIZE]), data, BLOCK_SIZE);
    time += L2_WRITE_TIME;
    Line->Dirty = 1;
  }
}

/*********************** L1 cache *************************/

void initCache() { SimpleCache1.init = 0; SimpleCache2.init = 0; }

void accessL1(uint32_t address, uint8_t *data, uint32_t mode) {

  uint32_t index, Tag, MemAddress, offset, word_index;
  uint8_t TempBlock[BLOCK_SIZE];

  /* init cache */
  if (SimpleCache1.init == 0) {  
    for (int i = 0; i < L1_SIZE/BLOCK_SIZE; i++)
      SimpleCache1.line[i].Valid = 0;
    SimpleCache1.init = 1;
  }
  offset = address % BLOCK_SIZE;
  index = (address/BLOCK_SIZE) % (L1_SIZE/BLOCK_SIZE);
  Tag = address/L1_SIZE;

  CacheLine *Line = &SimpleCache1.line[index];

  MemAddress = address - offset; // address of the block in memory

  /* access Cache*/

  if (!Line->Valid || Line->Tag != Tag) {         // if block not present - miss
    accessL2(MemAddress, TempBlock, MODE_READ); // get new block from L2

    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      MemAddress = (Line->Tag * L1_SIZE) | (index * BLOCK_SIZE); // get address of the block in memory
      accessL2(MemAddress, &(L1Cache[index * BLOCK_SIZE]),
                 MODE_WRITE); // then write back old block
    }

    memcpy(&(L1Cache[index * BLOCK_SIZE]), TempBlock,
           BLOCK_SIZE); // copy new block to cache line
    Line->Valid = 1;
    Line->Tag = Tag;
    Line->Dirty = 0;
  } // if miss, then replaced with the correct block

  word_index = offset / WORD_SIZE;

  if (mode == MODE_READ) {    // read data from cache line
    memcpy(data, &(L1Cache[index * BLOCK_SIZE + word_index * WORD_SIZE]), WORD_SIZE);
    time += L1_READ_TIME;
  }

  if (mode == MODE_WRITE) { // write data from cache line
    memcpy(&(L1Cache[index * BLOCK_SIZE + word_index * WORD_SIZE]), data, WORD_SIZE);
    time += L1_WRITE_TIME;
    Line->Dirty = 1;
  }
}

void read(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_READ);
}

void write(uint32_t address, uint8_t *data) {
  accessL1(address, data, MODE_WRITE);
}
