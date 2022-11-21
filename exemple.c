#include <stdio.h>
#include <fenv.h>

// L'affichage dépend du mode d'arrondi et non pas de la manière dont c'est stoqué

int main()
{
    double a = 1.0 / 124;
    printf("%lf \n", a);
    // store the original rounding mode
    const int originalRounding = fegetround( );
    // do wathever you need to do ...
    fesetround(FE_TOWARDZERO);
    // a = 1.0/124;
    printf("%lf \n", a);

    // ... and restore the original mode afterwards
    fesetround(originalRounding);
    // a = 1.0/124;
    printf("%lf \n", a);
    return 0;
}