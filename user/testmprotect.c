#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(void)
{
  char *base;
  char *p;
  int off;
  int pid;

  base = sbrk(0);
  off = (int)((uint)base % PGSIZE);
  if(off != 0){
    if(sbrk(PGSIZE - off) == (char*)-1){
      printf(1, "testmprotect: align sbrk failed\n");
      exit();
    }
  }

  p = sbrk(PGSIZE);
  if(p == (char*)-1){
    printf(1, "testmprotect: alloc failed\n");
    exit();
  }

  p[0] = 1;
  if(mprotect(p, 1) < 0){
    printf(1, "testmprotect: mprotect failed\n");
    exit();
  }

  pid = fork();
  if(pid < 0){
    printf(1, "testmprotect: fork failed\n");
    exit();
  }

  if(pid == 0){
    printf(1, "testmprotect: child writing protected page (should fault)\n");
    p[0] = 2;
    printf(1, "UNEXPECTED: child write succeeded\n");
    exit();
  }

  wait();

  if(munprotect(p, 1) < 0){
    printf(1, "testmprotect: munprotect failed\n");
    exit();
  }

  p[0] = 3;
  printf(1, "testmprotect: PASS\n");
  exit();
}
