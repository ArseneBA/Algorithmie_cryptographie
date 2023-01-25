// Libraries
#include "test.h"

// Function description
void test_nus_init()
{
    nus *a;
    int size = 0xff;
    nus_init(&a, size);

    for (int i=0; i < size; i++)
    {
        a->tab[i] = i;
    }

    nus_aff(a);

    nus_clear(&a);
}

void test_nus_clear()
{
    nus *a;
    int size = 0xff;
    nus_init(&a, size);

    for (int i=0; i < size; i++)
    {
        a->tab[i] = i;
    }

    nus_aff(a);

    nus_clear(&a);

    // Provoke a segmentation fault
    printf("%u", a->len);

    // Provoke a segmentation fault/ corrompt the memory
    for (int i=0; i < size; i++)
    {
        a->tab[i] = i;
    }
}

void test_nus_check_size()
{
    nus* test;
    nus_init(&test, 10);
    for (int i = 0; i < 10 - 2; i++)
    {
        test->tab[i] = (unsigned long long) 0;
    }
    test->tab[8] = 0;
    test->tab[9] = 0;

    nus_aff(test);

    nus_check_size(test);

    nus_aff(test);

    nus_clear(&test);
}

void test_nus_check_size_bool()
{
    nus* test;
/*     nus_init(&test, 10);
    for (int i = 0; i < 10; i++)
    {
        test->tab[i] = (unsigned long long) i;
    } */
    nus_init_0(&test, 4);
    test->tab[3] = 0x1;

    nus_aff(test);
    char res = nus_check_size_bool(test);
    if (res == 1)
        printf("TRUE\n");
    else
        printf("FALSE\n");

    test->tab[9] = 0;
    nus_aff(test);
    res = nus_check_size_bool(test);
    if (res == 1)
        printf("TRUE\n");
    else
        printf("FALSE\n");

    nus_clear(&test);    
}

void test_nus_add()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0xffffffffffffffff;
    a->tab[1] = 0x0;
    a->tab[2] = 0xffffffffffffffff;

    nus* b;
    nus_init(&b, 4);
    b->tab[0] = 0x1;
    b->tab[1] = 0x0;
    b->tab[2] = 0x1;
    b->tab[3] = 0x1;

    nus* c;
    c = nus_add(a, b);

    nus_aff(c);

    nus_clear(&a);
    nus_clear(&b);
}

void test_nus_sub()
{
    // <*> Sub by 0
    // <*> 2 equals nb
    // <*> simple sub (without carry)
    // <*> b>a, (more len and greater with same length)
    // <*> Sub with carry  
    nus *a;
    nus_init(&a, 4);
    a->tab[0] = 0x7b;
    a->tab[1] = 0xe125e2;
    a->tab[2] = 0x456;
    a->tab[3] = 0xe;

    nus* b;
    nus_init(&b, 1);
    b->tab[2] = 0xFFFFFFFFFFFFFFFF;
    b->tab[1] = 0xFFFFFFFFFFFFFFFE;
    b->tab[0] = 0xFFFFFFFFFFFFFFFF;

    nus* c;
    c = nus_sub(a, b);

    nus_aff_x(c);

    nus_clear(&a);
    nus_clear(&b);
    nus_clear(&c);
}

void test_nus_mul_llu()
{
    nus *b;
    nus_init(&b, 3);
    b->tab[0] = 0x8000000000000001;
    b->tab[1] = 0x0;
    b->tab[2] = 0x1;

    unsigned long long a_i = 0;

    nus* c;
    c = nus_mul_llu(a_i, b);

    nus_aff(c);

    nus_clear(&b); 
}

void test_nus_shift_b64_left()
{
    nus* a;
    nus_init(&a, 2);
    a->tab[0] = 0x1;
    a->tab[1] = 0x2;
    //a->tab[2] = 0x3;
    //a->tab[3] = 0x4;
    
    nus* b;
    b = nus_shift_b64_left(a, 1);
    nus* test;
    nus_init(&test, 10);
    nus_aff(a);
    nus_aff(b);

    nus_clear(&a);
    nus_clear(&b);
}

void test_nus_mul()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0x1;
    a->tab[1] = 0x0;
    a->tab[2] = 0x1;

    nus* b;
    nus_init(&b, 4);
    b->tab[0] = 0x0;
    b->tab[1] = 0x0;
    b->tab[2] = 0x0;
    b->tab[3] = 0x0;

    nus* c;
    c = nus_mul(a, b);

    nus_aff(c);

    nus_clear(&a);
    nus_clear(&b); 
}

void test_nus_shift_b2_right_1()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0xff;
    a->tab[1] = 0b1000;
    a->tab[2] = 0xff;

    nus_shift_b2_right_1(a);

    nus_aff_x(a);

    nus_clear(&a);   
}

void test_nus_shift_b2_right()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0xff;
    a->tab[1] = 0b1000;
    a->tab[2] = 0xff;

    nus_aff_x(a);

    nus_shift_b2_right(a, 4);

    nus_aff_x(a);

    nus_clear(&a);
}

void test_nus_comp()
{
    nus *a;
    nus_init(&a, 3);
    a->tab[0] = 0x0;
    a->tab[1] = 0x0;
    a->tab[2] = 0x1;

    nus* b;
    nus_init(&b, 3);
    b->tab[0] = 0x0;
    b->tab[1] = 0x0;
    b->tab[2] = 0x1;

    char c;
    c = nus_comp(a, b);

    printf("%x\n", c);

    nus_clear(&a);
    nus_clear(&b);    
}

void test_nus_mod()
{
    nus *m;
    nus_init(&m, 4);
    m->tab[0] = 0x0;
    m->tab[1] = 0xe12567;
    m->tab[2] = 0x456;
    m->tab[3] = 0x89;

    nus* res1, *res2;
    res1 = nus_mod(m);
    nus_aff_x(res1);

    res2 = nus_mod_naive(m);
    nus_aff_x(res2);

    nus_clear(&m);
}
