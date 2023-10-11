#ifndef TWOWAYL2CACHE_H
#define TWOWAYL2CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../Cache.h"

#define ASSOC_L2 2

void resetTime();

uint32_t getTime();

/****************  RAM memory (byte addressable) ***************/
void accessDRAM(uint32_t, uint8_t *, uint32_t);

/*********************** Cache *************************/

void initCache();
void accessL1(uint32_t, uint8_t *, uint32_t);
void accessL2(uint32_t, uint8_t *, uint32_t);

typedef struct Cache1Line {
  uint8_t Valid;
  uint8_t Dirty;
  uint32_t Tag;
} Cache1Line;

typedef struct Cache2Line {
  uint8_t Valid;
  uint8_t Dirty;
  uint32_t Tag;
  uint32_t Time;
} Cache2Line;


typedef struct CacheL1 {
  uint32_t init;
  Cache1Line line[L1_SIZE/BLOCK_SIZE];
} CacheL1;

typedef struct CacheL2 {
  uint32_t init;
  Cache2Line line[L2_SIZE/(BLOCK_SIZE*ASSOC_L2)][ASSOC_L2];
} CacheL2;

/*********************** Interfaces *************************/

void read(uint32_t, uint8_t *);

void write(uint32_t, uint8_t *);

#endif
