#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

#include <stdint.h>
#include <x86intrin.h>

/* Macro */
inline uint64_t START_TSC_READ(void)
{
  uint32_t a, d;

  __asm__ __volatile__ ( "xorl %%eax,%%eax\n"
                         "cpuid\n"
                         "rdtsc\n"
                         : "=a" (a), "=d" (d) : : 
  #ifdef __x86_64
                         "rbx", "rcx"
  #else
                         "ebx", "ecx"
  #endif                         
                       );

  return ((uint64_t)d << 32) | a;
}

inline uint64_t END_TSC_READ(void)
{
  uint32_t a, d;

  __asm__ __volatile__ ( "rdtscp\n"
                         : "=a" (a), "=d" (d) : : 
  #ifdef __x86_64
                         "rcx"
  #else
                         "ecx", "ecx"
  #endif                         
                       );

  return ((uint64_t)d << 32) | a;
}

#endif
