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
