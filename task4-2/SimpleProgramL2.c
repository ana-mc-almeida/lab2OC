#include "L2Cache.h"

int main() {

  uint32_t value1, clock;

  resetTime();
  initCache();
  value1 = -1;

  write(1, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(1, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  write(512, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(512, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  write(32769, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(32769, (uint8_t *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  return 0;
}
