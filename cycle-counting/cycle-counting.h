#ifndef __CYCLE_COUNTING_INCLUDED__
#define __CYCLE_COUNTING_INCLUDED__

#include <x86intrin.h>

/* Macro */
unsigned long inline START_TSC_READ(void)
{
  unsigned long r;

  __asm__ __volatile__ ( "mfence\n"
                         "rdtsc\n"
                         "shlq $32,%%rdx\n"
                         "orq  %%rdx,%%rax" : "=a" (r) : : "rdx" );

  return r;
}

unsigned long inline END_TSC_READ(void)
{
  unsigned long r;

  __asm__ __volatile__ ( "rdtscp\n"
                         "shlq $32,%%rdx\n"
                         "orq  %%rdx,%%rax" : "=a" (r) : : "rcx", "rdx" );
  return r;
}

#endif

