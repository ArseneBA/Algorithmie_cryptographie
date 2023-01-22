// Libraries
#include "test.h"

// Function description
void test_nus_init()
{
    nus *a;
    unsigned int size = 0xff;
    nus_init(&a, size);

    for (unsigned int i=0; i < size; i++)
    {
        a->tab[i] = i;
    }

    nus_aff(a);

    nus_clear(&a);
}

void test_nus_clear()
{
    nus *a;
    unsigned int size = 0xff;
    nus_init(&a, size);

    for (unsigned int i=0; i < size; i++)
    {
        a->tab[i] = i;
    }

    nus_aff(a);

    nus_clear(&a);

    // Provoke a segmentation fault
    printf("%u", a->len);

    // Provoke a segmentation fault/ corrompt the memory
    for (unsigned int i=0; i < size; i++)
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
        test->tab[i] = (unsigned long long) i;
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
    nus_init(&test, 10);
    for (int i = 0; i < 10; i++)
    {
        test->tab[i] = (unsigned long long) i;
    }

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
    // test retenue
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

void test_nus_mul_llu()
{
    nus *b;
    nus_init(&b, 3);
    b->tab[0] = 0x8000000000000001;
    b->tab[1] = 0x0;
    b->tab[2] = 0x1;

    unsigned long long a_i = 2;

    nus* c;
    c = nus_mul_llu(a_i, b);

    nus_aff(c);

    nus_clear(&b); 
}
