#include "task4-1/L1Cache.h"

int main() {

  int value1, value2, clock;

  resetTime();
  initCache();
  value1 = -1;
  value2 = 0;

  write(1, (unsigned char *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(1, (unsigned char *)(&value2));
  clock = getTime();
  printf("Time: %d\n", clock);

  write(8, (unsigned char *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(8, (unsigned char *)(&value2));
  clock = getTime();
  printf("Time: %d\n", clock);

  write(1, (unsigned char *)(&value1));
  clock = getTime();
  printf("Time: %d\n", clock);

  read(1, (unsigned char *)(&value2));
  clock = getTime();
  printf("Time: %d\n", clock);

  return 0;
}