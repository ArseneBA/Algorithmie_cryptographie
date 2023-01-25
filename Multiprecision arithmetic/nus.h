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
    int len;
} nus;


// Declaration of functions
void nus_aff(const nus* nb);
void nus_aff_x(const nus* nb);
void nus_init(nus **nb, const int len);
void nus_init_0(nus **nb, const int len);
void nus_clear(nus **nb);
void nus_cp(const nus* src, nus* dest);
void nus_check_size(nus *nb);
char nus_check_size_bool(const nus *nb);
char nus_is_zero(const nus* a);
nus* nus_add(const nus* a, const nus* b);
nus* nus_sub(const nus* a, const nus* b);
nus* nus_mul_llu(const unsigned long long a_i, const nus* b);
nus* nus_shift_b64_left(const nus* a, const int shift);
void nus_shift_b2_right_1(nus* a);
void nus_shift_b2_right(nus* a, const int shift);
char nus_comp(const nus* a, const nus* b);
nus* nus_mul(const nus* a, const nus* b);
nus* nus_mod(const nus* m);
nus* nus_mod_naive(const nus* m);
nus* nus_mul_mod(const nus* a, const nus* b, const nus* p);

#endif