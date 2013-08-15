#include <iostream>

#include "clock.h"
#include "common.h"
#include "ispc/saxpy.ispc.h"

#define ARRAY_SIZE (1024*1024)
#define LOOP_COUNT 128
#define MAXFLOPS_ITERS 100000000
#define FLOPSPERCALC 2
#define FREQUENCY 3.3e-9

using namespace std;

scalar_t A[ARRAY_SIZE] __attribute__((aligned(64)));
scalar_t B[ARRAY_SIZE] __attribute__((aligned(64)));
scalar_t a = 1.1;

inline void saxpy(scalar_t a, scalar_t *A, scalar_t *B, int num){
  for(int i = 0; i < num; i++)
    A[i] = a*A[i] + B[i];
}

int main(){
  double t = 0;

  for(int i = 0; i < ARRAY_SIZE; i++){
    A[i] = i + 0.1;
    B[i] = i + 0.2;
  }

  start_clock();
  for(int i = 0; i < MAXFLOPS_ITERS; i++){
    ispc::saxpy(a, A, B, LOOP_COUNT);
  }
  t = stop_clock()/1000.;

  double gflops = FREQUENCY * LOOP_COUNT * MAXFLOPS_ITERS *FLOPSPERCALC;
  cout << "ISPC: GFlops = " << gflops << ", Secs = " << t <<", GFlops per sec = " << gflops/t << endl;


  start_clock();
  for(int i = 0; i < MAXFLOPS_ITERS; i++){
    saxpy(a, A, B, LOOP_COUNT);
  }
  t = stop_clock()/1000.;

  cout << "Autovectorization: GFlops = " << gflops << ", Secs = " << t <<", GFlops per sec = " << gflops/t << endl;
}
