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
