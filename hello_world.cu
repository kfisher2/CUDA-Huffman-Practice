#include <iostream>
#include <cstdio>
#include <cstdlib>
// #include <helper_cuda.h>
// #include <helper_string.h>

/* Run with only HOST code *\
// Say goodbye to the world
int main(void) {
	printf("Goodbye World!\n");
	return 0;
}

*/


/* Run with DEVICE code */

__global__ void mykernel(void) { 
}

int main(void) {
  mykernel<<<1,1>>>();
  printf("Goodbye World!\n");
  return 0;
}

/*

__global__  indicates function that 1) runs on DEVICE , 2) called from the HOST

<<<   >>>   indicates function that    runs on DEVICE and is called from the HOST

*/
