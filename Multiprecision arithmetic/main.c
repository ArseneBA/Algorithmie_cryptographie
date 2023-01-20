
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <immintrin.h>

// Declaration of struct
typedef struct
{
    unsigned long long* tab;
    unsigned int len;
} Nb;


// Declaration of functions
/* void aff_Nb(const Nb* nb);
void init_Nb(Nb **nb, int len);
Nb* add(const Nb* a, const Nb* b); */

// Description of functions
void init_Nb(Nb **nb, int len)
{
    *nb = (Nb *) malloc(sizeof(Nb));
    (*nb)->tab = (unsigned long long *) malloc(sizeof(unsigned long long) * len);
    (*nb)->len = len;
}

void test_init_Nb()
{
    Nb *a;
    init_Nb(&a, (const int) 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0x3;
    a->tab[2] = 0xffffffffffffffff;
}

void aff_Nb(const Nb* nb)
{
    for (int i = nb->len - 1; i >= 0; i--)
    {
        printf("%llu ", nb->tab[i]);
    }
    printf("\n");
}

Nb* test(Nb* a, Nb* b)
{
    Nb* res;
    unsigned int size = 2;
    init_Nb(&res, size);
    
    return res;
}

Nb* add(const Nb* a, const Nb* b)
{
    Nb* res;
    unsigned int size;
    if (a->len > b->len)
    {
        printf("a\n");
        init_Nb(&res, a->len + 1);
        printf("Oh nooo\n");
        size = a->len;
    }
    else
    {
        //printf("b\n");
        init_Nb(&res, b->len + 1);
        size = b->len;
    }
    
    unsigned char r = 0;

    for (int i = 0; i < size - 1; i++)
    {
        r = _addcarry_u64(r, a->tab[i], b->tab[i], &res->tab[i]);
    }
    res->tab[size] = r;

    return res;
}

void test_add()
{
    // test retenue
    Nb *a;
    init_Nb(&a, 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0x3;
    a->tab[2] = 0xffffffffffffffff;

    Nb* b;
    init_Nb(&b, 3);
    b->tab[0] = 0x1;
    b->tab[1] = 0x5;
    b->tab[3] = 0x1;

    Nb* c;
    c = test(a, b);

    aff_Nb(c);

/*    Nb *a;
    init_Nb(&a, 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0xffffffffffffffff;
    a->tab[2] = 0xffffffffffffffff;

    Nb* b;
    init_Nb(&b, 2);
    b->tab[0] = 0x1;
    b->tab[1] = 0x0;

    Nb* c;
    c = add(a, b);

    aff_Nb(c); */
}

/* Nb* mul_Nb_long(const unsigned long long a_i, const Nb* b)
{
    Nb* res;
    init_Nb(&res, b->len + 1);

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
    Nb *a;
    init_Nb(&a, 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0xffffffffffffffff;
    a->tab[2] = 0xffffffffffffffff;

    Nb* b;
    init_Nb(&b, 2);
    b->tab[0] = 0x1;
    b->tab[1] = 0x0;

    Nb* c;
    c = add(a, b);

    aff_Nb(c);   
}
 */

int main()
{
    test_init_Nb();

    return 0;
}