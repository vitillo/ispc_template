#include "common.h"

inline void _saxpy(uniform scalar_t a, uniform scalar_t * uniform A, uniform scalar_t * uniform B, uniform int num, int idx){
  A[idx] = a*A[idx] + B[idx];
}

export void saxpy(uniform scalar_t a, uniform scalar_t * uniform A, uniform scalar_t * uniform B, uniform int num){
  foreach(i = 0 ... num){
    _saxpy(a, A, B, num, i);
  }
}
