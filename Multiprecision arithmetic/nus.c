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

void nus_aff_x(const nus* nb)
{
    printf("[");
    for (int i = nb->len - 1; i >= 0; i--)
    {
        printf("%llx ", nb->tab[i]);
    }
    printf("]\n");
}

void nus_init(nus **nb, const int len)
{
    *nb = (nus *) malloc(sizeof(nus));
    (*nb)->tab = (unsigned long long *) malloc(sizeof(unsigned long long) * len);
    (*nb)->len = len;
}

void nus_init_0(nus **nb, const int len)
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

void nus_cp(const nus* src, nus* dest)
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
        int head = nb->len - 1;
        while (nb->tab[head] == 0 && head != 0)
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
        int head = nb->len - 1;
        while (nb->tab[head] == 0 && head != 1)
            head--;
        if (head == nb->len - 1)
            return 1;
        else if(nb->tab[0] == 0)
            return 1;
        else
            return 0;
    }
}

nus* nus_add(const nus* a, const nus* b)
{
    nus* res;
    int size_h, size_l;
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
        nus_init(&res, b->len + 1);
        size_h = b->len;
        size_l = a->len;
        biggest = 'b';
    }
    
    unsigned char r = 0;

    for (int i = 0; i < size_l; i++)
    {
        r = _addcarry_u64(r, a->tab[i], b->tab[i], &res->tab[i]);
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

nus* nus_sub(const nus* a, const nus* b)
{
    nus* res;
    int size_h, size_l;

    if (nus_comp(a,b) == 1)
    {
        nus_init_0(&res, 1);
        return res;
    }
    else if(nus_comp(a,b) == 0)
    {
        perror("b is greater than a, it should not be !");
        exit(EXIT_FAILURE);
    }

    nus_init(&res, a->len);
    size_h = a->len;
    size_l = b->len;    

    unsigned char r = 0;
    for (int i = 0; i < size_l; i++)
    {
        r = _subborrow_u64(r, a->tab[i], b->tab[i], &res->tab[i]);
    }
    if (size_h != size_l)
    {
        for (int i = size_l; i < size_h; i++)
        {
            res->tab[i] = a->tab[i] - r;
            r = 0;
        }
    }
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

nus* nus_shift_b64_left(const nus* a, const int shift)
{
    nus* res;
    nus_init_0(&res, a->len + shift);
    nus_cp(a, res);

    unsigned long long next_part, prv_part; 

    for (int i = 0; i < shift; i++)
    {
        prv_part = 0;
        for (int j = 0; j < a->len + shift; j++)
        {
            next_part = res->tab[j];
            res->tab[j] = prv_part;
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

    nus* test;
    nus_init(&test, 10);

    for (int i = 0; i < a->len ; i++)
    {
        temp = nus_mul_llu(a->tab[i], b);
        
        nus_init(&test, 10);
        
        temp_o = temp;
        temp = nus_shift_b64_left(temp, i);
        
        nus_init(&test, 10);

        nus_clear(&temp_o);
        res_new = nus_add(res_old, temp);
        nus_clear(&res_old);
        res_old = res_new;
    }
    nus_check_size(res_new);
   
   return res_new;
}

void nus_shift_b2_right_1(nus* a)
{
    char ret_last = 0;
    char ret_next;

    unsigned long long mask = 0;
    mask = mask | ((unsigned long long) 1 << 63);

    for (int i = a->len - 1; i >= 0; i--)
    {
        ret_next = (char) ((a->tab[i] & 0x1));
        a->tab[i] = a->tab[i] >> 1;
        a->tab[i] = a->tab[i] | ((unsigned long long) ret_last << 63);
        ret_last = ret_next;
    }
}

void nus_shift_b2_right(nus* a, const int shift)
{
    for (int i = 0; i < shift && i < a->len * 64; i++)
        nus_shift_b2_right_1(a);
    nus_check_size(a);
}

/* void nus_shift_b2_right(nus* a, const int shift) // Works only if shift < 64
{
    unsigned long long ret_last = 0;
    unsigned long long ret_next;

    unsigned long long mask = 0;
    mask = mask | ((1 << shift) - 1);

    if (shift != 0)
    {
        for (int i = a->len - 1; i >= 0; i--)
        {
            ret_next = (a->tab[i] & mask) << (64 - shift);
            a->tab[i] = a->tab[i] >> shift;
            a->tab[i] = a->tab[i] | ret_last;
            ret_last = ret_next;
        }
    }
    nus_aff_x(a);
    nus_check_size(a);
    nus_aff_x(a);
} */

char nus_is_zero(const nus* a)
{
    // Return 0 if not, 1 if a = 0
    for (int i = 0; i < a->len; i++)
    {
        if (a->tab[i] != 0)
            return 0;
    }
    return 1;
}

char nus_comp(const nus* a, const nus* b)
{
    // Compare a and b, return 0 if a<b, 1 a==b, 2 a>b
    // We should check if a and/or b is/are 0
    if (nus_check_size_bool(a) != 1 ||  nus_check_size_bool(b) != 1)
        perror("The size of a and/or b did not match their saved len");

    if (nus_is_zero(a) == 1 && nus_is_zero(b) == 1)
        return 1;
    else if (nus_is_zero(a) == 1)
        return 0;
    else if (nus_is_zero(b) == 1)
        return 2;
    else if (a->len > b->len)
        return 2;
    else if(a->len < b->len)
        return 0;
    for (int i = a->len - 1; i >= 0; i--)
    {
        if (a->tab[i] > b->tab[i])
            return 2;
        else if (a->tab[i] < b->tab[i])
            return 0;
    }
    return 1;
}

nus* nus_mod(const nus* m)
{
    // We use p = 2^192-2^64-1, we calculated q' with q1.py
    nus* p, *q1;
    nus_init(&p, 3);
    p->tab[2] = 0xFFFFFFFFFFFFFFFF;
    p->tab[1] = 0xFFFFFFFFFFFFFFFE;
    p->tab[0] = 0xFFFFFFFFFFFFFFFF;

    nus_init_0(&q1, 4);
    q1->tab[3] = 0x1;

    nus* res;

    nus* m1, *mul, *q;
    nus_init(&m1, m->len);
    nus_cp(m, m1);

    nus_shift_b2_right(m1, 191);

    q = nus_mul(q1, m1);
    nus_clear(&m1);
    nus_shift_b2_right(q, 193);
    mul = nus_mul(p, q);
    nus_clear(&q);
    res = nus_sub(m, mul);
    nus_clear(&mul);

    nus* cp_add;
    while(nus_comp(res, p) == 2)
    {
        cp_add = res;
        res = nus_sub(res, p);
        nus_clear(&cp_add);
    }

    return res;
}

nus* nus_mod_naive(const nus* m)
{
    nus* p, *cp_add, *res;
    nus_init(&p, 3);
    p->tab[2] = 0xFFFFFFFFFFFFFFFF;
    p->tab[1] = 0xFFFFFFFFFFFFFFFE;
    p->tab[0] = 0xFFFFFFFFFFFFFFFF;

    nus_init(&res, m->len);
    nus_cp(m, res);

    while(nus_comp(res, p) == 2)
    {
        cp_add = res;
        res = nus_sub(res, p);
        nus_clear(&cp_add);
    }

    return res;
}

/* nus* nus_mul_mod(const nus* a, const nus* b, const nus* p)
{
    nus* res;
    nus_init_0(&res, a->len + b->len);

    nus* opp_inv_p;
    //opp_inv_p = nus_opp_inv(p);

    nus *add1, *add2, *mul1, *mul2, *q;

    nus_init_0(&q, 1);

    for (int i = 0; i < p->len; i++ )
    {
        mul1 = nus_mul(a->tab[i], b->tab[0]);
        add1 = nus_add(res->tab[0], mul1);
        nus_clear(&mul1);
        mul1 = nus_mul(add1, opp_inv_p);
        nus_clear(&add1);
        q->tab[0] = ((mul1->tab[0] && 0x1) || 0x0000000000000000);
        nus_clear(&mul1);

        mul1 = nus_mul(a->tab[i], b);
        mul2 = nus_mul(q, p);
        nus_clear(&q);
        add1 = nus_add(res, mul1);
        nus_clear(&mul1);
        nus_clear(&res);
        add2 = nus_add(add1, mul2);
        nus_clear(&mul1);
        nus_clear(&add1);
        //res = nus_div2(add2);
        nus_clear(&add2);
    }
    if (nus_comp(res, p) == 2)
    {
        //res = nus_sub(r, p);
    }

    return res;
} */
