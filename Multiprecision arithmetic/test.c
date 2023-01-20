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
}

void test_nus_check_size()
{
    nus* test;
    nus_init(&test, 10);
    for (int i = 0; i < 10 - 1; i++)
    {
        test->tab[i] = (unsigned long long) i;
    }
    test->tab[9] = 0;

    nus_aff(test);

    nus_check_size(test);

    nus_aff(test);
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

    nus* c;
    c = nus_add(a, b);

    nus_aff(c);
}
