
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <immintrin.h>

#include "nus.h"
#include "test.h"

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
nus* nus_add(const nus* a, const nus* b);

// Description of functions
void nus_init(nus **nb, const unsigned int len)
{
    *nb = (nus *) malloc(sizeof(nus));
    (*nb)->tab = (unsigned long long *) malloc(sizeof(unsigned long long) * len);
    (*nb)->len = len;
}

void nus_clear(nus **nb)
{
    // To write
}

void nus_check_size(nus *nb)
{
    unsigned int head = nb->len - 1;
    while (nb->tab[head] == 0)
        head--;
    if (head != nb->len - 1)
    {
        nb->tab = (unsigned long long*) realloc(nb->tab, sizeof(unsigned long long) * (head + 1));
        nb->len = head + 1;
    }
}

void nus_aff(const nus* nb)
{
    printf("[");
    for (int i = nb->len - 1; i >= 0; i--)
    {
        printf("%llu ", nb->tab[i]);
    }
    printf("]\n");
}

nus* nus_add(const nus* a, const nus* b)
{
    nus* res;
    unsigned int size;
    if (a->len > b->len)
    {
        printf("a\n");
        nus_init(&res, a->len + 1);
        printf("Oh nooo\n");
        size = a->len;
    }
    else
    {
        //printf("b\n");
        nus_init(&res, b->len + 1);
        size = b->len;
    }
    
    unsigned char r = 0;

    for (int i = 0; i < size; i++)
    {
        printf("r_before = %hhu, ", r);
        printf("a[%d] + a[%d] = %llu + %llu = ", i, i, a->tab[i], b->tab[i]);
        r = _addcarry_u64(r, a->tab[i], b->tab[i], &res->tab[i]);
        printf("%llu, ", res->tab[i]);
        printf("r_after = %hhu\n", r);
    }
    res->tab[size] = r;

    return res;
}

/* nus* mul_Nb_long(const unsigned long long a_i, const nus* b)
{
    nus* res;
    nus_init(&res, b->len + 1);

    unsigned long long dl, dh;

    res->tab[0] = 0;

    __uint128_t mul_intermediate;
    unsigned char retenue = 0, retenue_2 = 0;

    for (int j = 0; j < b->len; j++)
    {
        mul_intermediate = (__uint128_t) a_i * b->tab[j];
        dh = mul_intermediate >> 64;
        dl = mul_intermediate;

        retenue = _addcarry_u64((char) 0, res->tab[j], dl, &res->tab[j]);
        res->tab[j+1] = dh;

        retenue_2 = _addcarry_u64(retenue, res->tab[j+1], retenue_2, &res->tab[j+1]);
    }

    return res;
}

void test_add()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0xffffffffffffffff;
    a->tab[2] = 0xffffffffffffffff;

    nus* b;
    nus_init(&b, 2);
    b->tab[0] = 0x1;
    b->tab[1] = 0x0;

    nus* c;
    c = nus_add(a, b);

    nus_aff(c);   
}
 */

int main()
{
    test_nus_check_size();

    return 0;
}