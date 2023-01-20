
// Libraries
#include <stdio.h>
#include <stdlib.h>

#include "nus.h"
#include "test.h"

// Program
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