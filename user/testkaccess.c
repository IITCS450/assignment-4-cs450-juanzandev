#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  volatile int *p;
  volatile int x;

  printf(1, "testkaccess: illegal read attempt\n");
  p = (int*)0xFFFF0000;
  x = *p;
  printf(1, "UNEXPECTED: read=%d\n", x);
  exit();
}
