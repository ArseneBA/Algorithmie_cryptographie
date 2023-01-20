#ifndef NUS_H
#define NUS_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <immintrin.h>


// Declaration of struct
    //Number of undetermined size : nus
typedef struct
{
    unsigned long long* tab;
    unsigned int len;
} nus;


// Declaration of functions
void nus_aff(const nus* nb);
void nus_init(nus **nb, const unsigned int len);
void nus_clear(nus **nb);
void nus_check_size(nus *nb);
nus* nus_add(const nus* a, const nus* b);

#endif