#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  volatile int *p;
  volatile int x;

  printf(1, "testnull: about to dereference NULL\n");
  p = (int*)0x0;
  x = *p;
  printf(1, "UNEXPECTED: read=%d\n", x);
  exit();
}
