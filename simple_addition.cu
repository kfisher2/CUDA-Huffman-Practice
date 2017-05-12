#include <iostream>
#include <cstdlib>
#include <cstdio>

__global__ void add(int *a, int *b, int *c) {
  *c = *a + *b;
}

int main(void) {
  int a, b, c;          // HOST copies of a, b, c
  int *d_a, *d_b, *d_c;    // DEVICE copies of a, b, c
  
  int size = sizeof(int);

  // Allocate space on DEVICE for DEVICE copies d_a, d_b, d_c
  cudaMalloc(&d_a, size);
  cudaMalloc(&d_b, size);
  cudaMalloc(&d_c, size);

  // Set input values
  a = 2;
  b = 7;

  // Copy inputs to DEVICE
  cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

  // Launch add() kernel on DEVICE
  add<<<1,1>>>(d_a, d_b, d_c);

  // Copy result back to HOST
  cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

  // Test
  if(c != a + b) std::cout << "Incorrect addition with result: " << c << '\n';

  //Clean-up 
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  return 0;

}

/* Moving to parallel

add<<<N, 1>>> we can execute add() N times in parallel

each parallel invocation is called a BLOCK
the collectino fo blocks is called a GRID

each invocation can refer to it's BLOCK index with
  blockIdx.x




*/