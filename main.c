#include <stdio.h>
#include <fenv.h>
#include <stdlib.h>
#include <math.h>


// Macro
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

// Function declaration for interval arithmetic
struct Double_interval to_interval(char* x_string);
void add(struct Double_interval x1, struct Double_interval x2, struct Double_interval res);
struct Double_interval add_r(struct Double_interval x1, struct Double_interval x2);
void sous(struct Double_interval x1, struct Double_interval x2, struct Double_interval res);
struct Double_interval sous_r(struct Double_interval x1, struct Double_interval x2);
void mult(struct Double_interval x1, struct Double_interval x2, struct Double_interval res);
struct Double_interval mult_r(struct Double_interval x1, struct Double_interval x2);
void pow_2(struct Double_interval x, struct Double_interval res);
struct Double_interval pow_2_r(struct Double_interval x);
void sqrt_root(struct Double_interval x, struct Double_interval res);
struct Double_interval sqrt_root_r(struct Double_interval x);
void inv(struct Double_interval x, struct Double_interval res);
struct Double_interval inv_r(struct Double_interval x);
void aff(struct Double_interval x);
void validate();

// Function declaration for test function
void poly_root(char* a_s, char* b_s, char* c_s, struct Double_interval* res);

// Structures
struct Double_interval
{
    // d : lower bound
    // u : upper bound
    double d, u;
};

// global variables
const int original_rounding = 0;  // fegetround( ) returns 0

// Function description
struct Double_interval to_interval(char* x_string)
{
    struct Double_interval res;

    fesetround(FE_UPWARD);
    res.u = atof(x_string);
    //printf("%lf ", res.u);
    fesetround(FE_DOWNWARD);
    res.d = atof(x_string);
    //printf("%lf \n", res.d);

    fesetround(original_rounding);

    return res;
}

void add(struct Double_interval x1, struct Double_interval x2, struct Double_interval res)
{
    fesetround(FE_DOWNWARD);
    res.d = x1.d + x2.d;

    fesetround(FE_UPWARD);
    res.u = x1.u + x2.u;

    fesetround(original_rounding);
}

struct Double_interval add_r(struct Double_interval x1, struct Double_interval x2)
{
    struct Double_interval res;

    fesetround(FE_DOWNWARD);
    res.d = x1.d + x2.d;

    fesetround(FE_UPWARD);
    res.u = x1.u + x2.u;

    fesetround(original_rounding);

    return res;
}

void sous(struct Double_interval x1, struct Double_interval x2, struct Double_interval res)
{
    fesetround(FE_DOWNWARD);
    res.d = x1.d - x2.u;

    fesetround(FE_UPWARD);
    res.u = x1.u - x2.d;

    fesetround(original_rounding);
}

struct Double_interval sous_r(struct Double_interval x1, struct Double_interval x2)
{
    struct Double_interval res;

    fesetround(FE_DOWNWARD);
    res.d = x1.d - x2.u;

    fesetround(FE_UPWARD);
    res.u = x1.u - x2.d;

    fesetround(original_rounding);

    return res;
}

void mult(struct Double_interval x1, struct Double_interval x2, struct Double_interval res)
{
    fesetround(FE_DOWNWARD);
    res.d = MIN(MIN(x1.d * x2.u, x1.d * x2.d), MIN(x1.u * x2.u, x1.u * x2.d));

    fesetround(FE_UPWARD);
    res.u = MAX(MAX(x1.d * x2.u, x1.d * x2.d), MAX(x1.u * x2.u, x1.u * x2.d));

    fesetround(original_rounding);
}

struct Double_interval mult_r(struct Double_interval x1, struct Double_interval x2)
{
    struct Double_interval res;

    fesetround(FE_DOWNWARD);
    res.d = MIN(MIN(x1.d * x2.u, x1.d * x2.d), MIN(x1.u * x2.u, x1.u * x2.d));

    fesetround(FE_UPWARD);
    res.u = MAX(MAX(x1.d * x2.u, x1.d * x2.d), MAX(x1.u * x2.u, x1.u * x2.d));

    fesetround(original_rounding);

    return res;
}

void pow_2(struct Double_interval x, struct Double_interval res)
{
    if (x.u != 0 || x.d != 0)
    {
        fesetround(FE_DOWNWARD);
        res.d = MIN(x.d * x.d, x.u * x.u);

        fesetround(FE_UPWARD);
        res.u = MAX(x.d * x.d, x.u * x.u);
    }
    else
    {
        fesetround(FE_DOWNWARD);
        res.d = 0.0;

        fesetround(FE_UPWARD);
        res.u = MAX(x.d * x.d, x.u * x.u);
    }

    fesetround(original_rounding);
}

struct Double_interval pow_2_r(struct Double_interval x)
{
    struct Double_interval res;

    if (x.u != 0 || x.d != 0)
    {
        fesetround(FE_DOWNWARD);
        res.d = MIN(x.d * x.d, x.u * x.u);

        fesetround(FE_UPWARD);
        res.u = MAX(x.d * x.d, x.u * x.u);
    }
    else
    {
        fesetround(FE_DOWNWARD);
        res.d = 0.0;

        fesetround(FE_UPWARD);
        res.u = MAX(x.d * x.d, x.u * x.u);
    }

    fesetround(original_rounding);

    return res;
}

void sqrt_root(struct Double_interval x, struct Double_interval res)
{
    // à faire
    if (x.d > 0)
    {
        fesetround(FE_DOWNWARD);
        x.d = sqrt(x.d);

        fesetround(FE_UPWARD);
        x.u = sqrt(x.u);

        fesetround(original_rounding);
    }
    else
    {
        printf("No square root for negative number in the Real.\n");
    }
}

struct Double_interval sqrt_root_r(struct Double_interval x)
{
    struct Double_interval res;
    if (x.d > 0)
    {
        fesetround(FE_DOWNWARD);
        res.d = sqrt(x.d);

        fesetround(FE_UPWARD);
        res.u = sqrt(x.u);

        fesetround(original_rounding);
    }
    else
    {
        printf("No square root for negative number in the Real.\n");
    }

    return res;
}

void inv(struct Double_interval x, struct Double_interval res)
{
    if (x.d > 0 || x.u < 0)
    {
        fesetround(FE_DOWNWARD);
        res.d = 1.0/x.u;

        fesetround(FE_UPWARD);
        res.u = 1.0/x.d;
    }
    else
    {
        printf("Warning : divided by 0.\n");
    }
}

struct Double_interval inv_r(struct Double_interval x)
{
    struct Double_interval res;

    if (x.d > 0 || x.u < 0)
    {
        fesetround(FE_DOWNWARD);
        res.d = 1.0/x.u;

        fesetround(FE_UPWARD);
        res.u = 1.0/x.d;
    }
    else
    {
        printf("Warning : divided by 0.\n");
    }

    return res;
}

void validate()
{
    char* x_string_1 = "0.1";
    char* x_string_2 = "0.2";
    struct Double_interval x1, x2;
    
    x1 = to_interval(x_string_1);
    aff(x1);
    x2 = to_interval(x_string_2);
    aff(x2);

    printf("Add : \t\t");
    aff(add_r(x1, x2));
    printf("Soustract : \t");
    aff(sous_r(x2, x1));
    printf("Multiply : \t");
    aff(mult_r(x1, x2));
    printf("Square : \t");
    aff(pow_2_r(x2));
    printf("Square root : \t");
    aff(sqrt_root_r(x2));
    printf("Inversion : \t");
    aff(inv_r(x2));
}

void aff(struct Double_interval x)
{
    fesetround(FE_DOWNWARD);
    printf("[%lf ;", x.d);

    fesetround(FE_UPWARD);
    printf(" %lf]\n", x.u);

    fesetround(original_rounding);
}

void poly_root(char* a_s, char* b_s, char* c_s, struct Double_interval* res)
{
    struct Double_interval a, b, c, nb_0, nb_2, nb_4, delta;

    a = to_interval(a_s);
    b = to_interval(b_s);
    c = to_interval(c_s);

    nb_0 = to_interval("0.0");
    nb_2 = to_interval("2.0");
    nb_4 = to_interval("4.0");

    delta = sous_r(pow_2_r(b), mult_r(mult_r(nb_4, a), c));

    if (delta.d > 0)
    {
        res[0] = mult_r(sous_r(sqrt_root_r(delta), b), inv_r(mult_r(nb_2, a))); 
        res[1] = mult_r(sous_r(sous_r(nb_0, b), sqrt_root_r(delta)), inv_r(mult_r(nb_2, a)));
    }
    else if (delta.u < 0)
    {
        printf("Complex \n");
    }
    else
    {
        res[0] = res[1] = mult_r(sous_r(nb_0, b), inv_r(mult_r(nb_2, a)));
    }
    aff(res[0]);
    aff(res[1]);
}

void validation_poly()
{
    struct Double_interval res[2];

    poly_root("1.0", "2000", "-3.0", res);

    poly_root("2.0", "-4000", "-1.0", res);

    poly_root("5.0", "8000", "2.0", res);    
}

// main
int main(void)
{
    return 0;
}
