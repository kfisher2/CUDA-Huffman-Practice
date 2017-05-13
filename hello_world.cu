#include <iostream>
#include <cstdio>
#include <cstdlib>
// #include <helper_cuda.h>
// #include <helper_string.h>

/* Run with only HOST code *\

// Say goodbye to the universe
int main(void) {
	printf("Heat death boogaloo!\n");
	return 0;
}

*/


/* Run with DEVICEEEEEEE code */

__global__ void mykernel(void) { 
}

int main(void) {
  mykernel<<<1,1>>>();
  printf("HEat death boogaloo Universe!\n");
  return 0;
}

/*
blah blah comment not conflicting
__global__  indicates function that 1) runs on DEVICE , 2) called from the HOST

<<<   >>>   indicates function that    runs on DEVICE and is called from the HOST

*////////
