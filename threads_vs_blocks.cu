#include <iostream>
#include <cstdlib>
#include <cstdio>

__global__ void add(int *a, int *b, int *c) {
  /*       BLOCKS        */
  // c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
  /*       VS THREADS    */
  c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
}

// RAWRRRRRRR COMMENT blah
void random_ints(int *a, int N) {
  for(int i = 0; i < N; ++i) {
    a[i] = rand();
  }
}

#define N 512
int main(void) {
  int *a, *b, *c;          // HOST copies of a, b, c
  int *d_a, *d_b, *d_c;    // DEVICE copies of a, b, c
  
  int size = N * sizeof(int);

  // Allocate space on DEVICE for DEVICE copies of a, b, c
  cudaMalloc((void **)&d_a, size);
  cudaMalloc((void **)&d_b, size);
  cudaMalloc((void **)&d_c, size);
  // Allocate space on HOST for HOST copies of a, b, c
  a = (int *)malloc(size);
  b = (int *)malloc(size);
  c = (int *)malloc(size);

  // Set input values
  random_ints(a,N);
  random_ints(b,N);

  // Copy inputs to DEVICE
  cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

  // Launch add() kernel on DEVICE
  /*  BLOCKS      */
  // add<<<N,1>>>(d_a, d_b, d_c);
  /*  VS THREADS  */
  add<<<1,N>>>(d_a, d_b, d_c);

  // Copy result back to HOST
  cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

  // Test
  // would need loop now, too lazy
  // if(c != a + b) std::cout << "Incorrect addition with result: " << c << '\n';

  //Clean-up 
  free(a); free(b); free(c);
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
