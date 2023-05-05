#include <stdio.h>
#include <stdlib.h>

int g0;       /* global variable, uninitialized */
int g1 = 14;  /* global variable, initialized */
int g2[1500]; /* global variable, uninitialized */
int g3 = 16;  /* global variable, initialized */
int g4;       /* global variable, uninitialized */

void proc1();
void proc2();

int main()
{
  extern int etext[], edata[], end[];

  int lc0;        /* local variable, stored on stack */
  int lc1 = 27;   /* local variable, stored on stack; mix init and uninit */
  int lc2;        /* local variable, stored on stack */
  static int ls0; /* local static variable, uninitialized data */
  static int ls1 = 19; /* local static variable, initialized data */
  int *pheap1;
  int *pheap2;

  pheap1 = (int *)malloc(sizeof(int));
  pheap2 = (int *)malloc(sizeof(int));

  printf("\n\n---------- main -------------------\n\n");
  printf("%14s : Last address\n", "0xffffffffffff");

  printf("%14p : Address etext\n", etext);
  printf("%14p : Address edata\n", edata);
  printf("%14p : Address end\n", end);

  printf("%14p : Address of code for proc1\n", &proc1);
  printf("%14p : Address of code for proc2\n", &proc2);

  printf("%14p : Address of uninitialized global variable g0\n", &g0);
  printf("%14p : Address of initialized   global variable g1\n", &g1);
  printf("%14p : Address of uninitialized global array    g2\n", &g2[0]);
  printf("%14p : Address of initialized   global variable g3\n", &g3);
  printf("%14p : Address of uninitialized global variable g4\n", &g4);

  printf("%14p : Address heap1 in heap space\n", pheap1);
  printf("%14p : Address heap2 in heap space\n", pheap2);

  printf("%14p : Address of local variable lc0\n", &lc0);
  printf("%14p : Address of local variable lc1\n", &lc1);
  printf("%14p : Address of local variable lc2\n", &lc2);

  printf("%14p : Address of local uninitialized static var ls0\n", &ls0);
  printf("%14p : Address of local initialized   static var ls1\n", &ls1);

  proc1();
  proc2();

  return 0;
}

void proc1()
{
  int lc3;
  int lc4 = 37;

  printf("\n\n----------- proc1 ------------------\n\n");
  printf("%14p : Address of code for proc1\n", &proc1);
  printf("%14p : Address of global variable g0\n", &g0);
  printf("%14p : Address of global variable g1\n", &g1);
  printf("%14p : Address of global variable g2\n", &g2[0]);
  printf("%14p : Address of global variable g3\n", &g3);
  printf("%14p : Address of global variable g4\n", &g4);
  printf("%14p : Address of local variable lc3\n", &lc3);
  printf("%14p : Address of local variable lc4\n", &lc4);
}

void proc2()
{
  int lc5;
  int lc6 = 51;
  static int ls2;
  static int ls3 = 47;

  printf("\n\n------------ proc2 -----------------\n\n");
  printf("%14p : Address of code for proc2\n", &proc2);
  printf("%14p : Address of global variable g0\n", &g0);
  printf("%14p : Address of global variable g1\n", &g1);
  printf("%14p : Address of global variable g2\n", &g2[0]);
  printf("%14p : Address of global variable g3\n", &g3);
  printf("%14p : Address of global variable g4\n", &g4);
  printf("%14p : Address of local variable lc5\n", &lc5);
  printf("%14p : Address of local variable lc6\n", &lc6);
  printf("%14p : Address of local uninitialized static var ls2\n", &ls2);
  printf("%14p : Address of local initialized   static var ls3\n", &ls3);
}