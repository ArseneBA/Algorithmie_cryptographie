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

void nus_init_0(nus **nb, const unsigned int len)
{
    nus_init(nb, len);

    for (int i = 0; i < len; i++)
        (*nb)->tab[i] = 0;
}

void nus_clear(nus **nb)
{
    free((*nb)->tab);
    free(*nb);
    *nb = NULL;
}

void nus_cp(nus* src, nus* dest)
{
    if (src->len > dest->len)
        perror("Destination must be longer than source");
    
    for (int i = 0; i < src->len; i++)
        dest->tab[i] = src->tab[i];
}

void nus_check_size(nus *nb)
{
    if (nb->len != 1)
    {
        unsigned int head = nb->len - 1;
        while (nb->tab[head] == 0 && head != 1)
            head--;
        if (nb->tab[head] != 0)
        {
            if (head != nb->len - 1)
            {
                nb->tab = (unsigned long long*) realloc(nb->tab, sizeof(unsigned long long) * (head + 1));
                nb->len = head + 1;
            }
        }
    }
}

char nus_check_size_bool(const nus *nb)
{
    if (nb->len != 1)
    {
        unsigned int head = nb->len - 1;
        while (nb->tab[head] == 0 && head != 1)
            head--;
        if (head == nb->len - 1)
            return 1;
        else
            return 0;
    }
}

nus* nus_add(const nus* a, const nus* b)
{
    nus* res;
    unsigned int size_h, size_l;
    char biggest;

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

nus* nus_shift_left(nus* a, const unsigned int shift) // Not wrk
{
    nus* res;
    nus_init_0(&res, a->len + shift);
    nus_cp(a, res);

    unsigned long long next_part, prv_part; 

    prv_part = 0;

    for (int i = 0; i < shift; i++)
    {
        for (int j = -1; j < 5; j++)
        {
            next_part = res->tab[j + 1];
            res->tab[j + 1] = prv_part;
            prv_part = next_part;
        }
    }

    return res;
}

nus* nus_mul(const nus* a, const nus* b)
{
    if (nus_check_size_bool(a) != 1 || nus_check_size_bool(b) != 1)
    {
        perror("The size of a and/or b did not match their saved len");
    }

    nus* res_old, *res_new;
    nus* temp, *temp_o;

    nus_init_0(&res_old, a->len + b->len);

    for (int i = 0; i < a->len ; i++)
    {
        printf("i : %d\ntemp : ", i);
        temp = nus_mul_llu(a->tab[i], b);
        nus_aff(temp);
        temp_o = temp;
        temp = nus_shift_left(temp, i);
        nus_aff(temp);
        nus_clear(&temp_o);
        nus_aff(res_old);
        res_new = nus_add(res_old, temp);
        nus_aff(res_new);
        nus_clear(&res_old);
        res_old = res_new;
    }
    nus_check_size(res_new);
   
   return res_new;
}
