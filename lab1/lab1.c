/*
James Sieben 200455325

3. Addresses get smaller.
4. Yes, some variables share the same address because they are used in different processes.
5. I'd expect them to be stored locally in the stack.
   After running the program, it appears the variables store in the stack.

       +------------------+
       |  TEXT            | 0x556752059249 = main
       |                  | 0x56299e4f23d2 = proc1
       |  instructions in | 0x56299e4f24d7 = proc2
       |  machine code    | 
       |                  |
       +------------------+ 0x56299e4f2695 = etext
       |  DATA            | 0x56299e4f5010 = g1
       |  - initialized   | 0x56299e4f5014 = g3
       |    variables     | 0x56299e4f5018 = ls1
       |                  | 0x56299e4f501c = ls3
       |                  |
       | ---------------  | 0x56299e4f5020  = edata
       |                  | 0x56299e4f5024 = ls0
       |                  | 0x56299e4f5028 = ls2
       |                  | 0x56299e4f5040 = g4
       |  - uninitialized | 0x56299e4f5044 = g0
       |    variables     | 0x56299e4f5060 = g2
       |                  |
       |                  |
       | ---------------  | 0x56299e4f67d0 = end
       |  - heap for      | 0x5629a00a52a0 = heap1
       |  dynamic         | 0x5629a00a52c0 = heap2
       |  allocation      |
       |                  |
       |                  |
       +------------------+
                |
                |
                V

                .
                .
                .

                ^
                |
                |
       +------------------+
       |  STACK           | 0x7ffd3e37ae40 = lc3
       |  - function      | 0x7ffd3e37ae40 = lc5
       |    activation    | 0x7ffd3e37ae44 = lc4
       |    records       | 0x7ffd3e37ae44 = lc6
       |  - local         | 0x7ffd3e37ae6c = lc0
       |    automatic     | 0x7ffd3e37ae70 = lc1
       |    variables     | 0x7ffd3e37ae74 = lc2
       +------------------+
*/ 

#include <stdio.h>

// Function computes the factorial of a # passed by reference
int factorial(int a)
{
       printf("%14p : Address of code for factorial\n", &factorial);
       printf("%14p : Address of code for int a\n", &a);
       if (a == 1)
       {
              return a;
       }
       else
       {
              return a * factorial(a - 1);
       }
} // End factorial

// Main function asks for a number and calls factorial function
int main()
{
       int a;
       printf("What factorial would you like to compute? ");
       scanf("%i", &a);

       int b = factorial(a);
       printf("The answer is: %d\n", b);
} // End main