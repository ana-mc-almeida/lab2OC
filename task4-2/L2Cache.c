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
  uint32_t index, tag, MemAddress;

  /* init cache */
  if (SimpleCache2.init == 0) {  
    for (int i = 0; i < L2_SIZE/BLOCK_SIZE; i++)
      SimpleCache2.line[i].Valid = 0;
    SimpleCache2.init = 1;
  }
  index = (address/BLOCK_SIZE) % (L2_SIZE/BLOCK_SIZE);
  tag = address/L2_SIZE;

  CacheLine *Line = &SimpleCache2.line[index];

  /* access Cache*/
  if (!Line->Valid || Line->Tag != tag) {  // if block not present - miss
    
    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      // get address of the block in memory
      MemAddress = (Line->Tag * L2_SIZE) + (index * BLOCK_SIZE);
      accessDRAM(MemAddress, &(L2Cache[index * BLOCK_SIZE]),
                 MODE_WRITE); // first write back old block
    }

    // get new block from DRAM and copy it to cache line
    accessDRAM(address, &(L2Cache[index * BLOCK_SIZE]), MODE_READ);

    Line->Valid = 1;
    Line->Tag = tag;
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

  uint32_t index, tag, MemAddress, offset, word_index;

  /* init cache */
  if (SimpleCache1.init == 0) {  
    for (int i = 0; i < L1_SIZE/BLOCK_SIZE; i++)
      SimpleCache1.line[i].Valid = 0;
    SimpleCache1.init = 1;
  }
  offset = address % BLOCK_SIZE;
  index = (address/BLOCK_SIZE) % (L1_SIZE/BLOCK_SIZE);
  tag = address/L1_SIZE;

  CacheLine *Line = &SimpleCache1.line[index];

  /* access Cache*/

  if (!Line->Valid || Line->Tag != tag) { // if block not present - miss
  
    if ((Line->Valid) && (Line->Dirty)) { // line has dirty block
      // get address of the block in memory
      MemAddress = ((Line->Tag * L1_SIZE) + (index * BLOCK_SIZE));
      accessL2(MemAddress, &(L1Cache[index * BLOCK_SIZE]),
                 MODE_WRITE); // first write back old block
    }

    // get new block from L2 and copy it to cache line
    accessL2(address, &(L1Cache[index * BLOCK_SIZE]), MODE_READ);
    Line->Valid = 1;
    Line->Tag = tag;
    Line->Dirty = 0;
  } // if miss, then replaced with the correct block

  word_index = offset / WORD_SIZE; // word inside block

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
