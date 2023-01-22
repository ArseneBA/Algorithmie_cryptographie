// Library
#include "nus.h"

// Function description
void nus_aff(const nus* nb)
{
    printf("[");
    for (int i = nb->len - 1; i >= 0; i--)
    {
        printf("%llu ", nb->tab[i]);
    }
    printf("]\n");
}

void nus_init(nus **nb, const unsigned int len)
{
    *nb = (nus *) malloc(sizeof(nus));
    (*nb)->tab = (unsigned long long *) malloc(sizeof(unsigned long long) * len);
    (*nb)->len = len;
}

void nus_clear(nus **nb)
{
    free((*nb)->tab);
    free(*nb);
    *nb = NULL;
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

char nus_check_size_bool(const nus *nb)
{
    unsigned int head = nb->len - 1;
    while (nb->tab[head] == 0)
        head--;
    if (head == nb->len - 1)
        return 1;
    else
        return 0;
}

nus* nus_add(const nus* a, const nus* b)
{
    nus* res;
    unsigned int size_h, size_l;
    char biggest;

    // Per security, we check the size of a and b, if there were not the correct size an error (compile-time) will be raised
    // because the const is not respected
    if (nus_check_size_bool(a) == 1 && nus_check_size_bool(b) == 1)
    {
        if (a->len > b->len)
        {
            nus_init(&res, a->len + 1);
            size_h = a->len;
            size_l = b->len;
            biggest ='a';
        }
        else
        {
            //printf("b\n");
            nus_init(&res, b->len + 1);
            size_h = b->len;
            size_l = a->len;
            biggest = 'b';
        }
        
        unsigned char r = 0;

        for (int i = 0; i < size_l; i++)
        {
            printf("a[%d] + b[%d] + r = %llu + %llu + %hhu = ", i, i, a->tab[i], b->tab[i], r);
            r = _addcarry_u64(r, a->tab[i], b->tab[i], &res->tab[i]);
            printf("%llu, ", res->tab[i]);
            printf("r_after = %hhu\n", r);
        }
        if (size_h != size_l)
        {
            for (int i = size_l; i < size_h; i++)
            {
                if (biggest == 'a')
                    res->tab[i] = a->tab[i] + r;
                else
                    res->tab[i] = b->tab[i] + r;
                r = 0;
            }
        }
        else
            res->tab[size_h] = r;

        nus_check_size(res);

        return res;
    }
    else
        perror("The size of a and/or b did not match their saved len");
}

nus* nus_mul_llu(const unsigned long long a_i, const nus* b)
{
    nus* res;
    if (nus_check_size_bool(b) != 1)
    {
        perror("The size of a did not match its saved len");
    }
    
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

    nus_check_size(res);

    return res;
}

nus* nus_mul(const nus* a, const nus* b)
{

}