#include <stdio.h>

int main() {
    int a;
    double b;

    // Marrja e input-it
    printf("Shkruaj nje numer int: ");
    scanf("%d", &a);

    printf("Shkruaj nje numer double: ");
    scanf("%lf", &b);

    // Pointerat
    int *pA = &a;
    double *pB = &b;

    // Ruaj vlerat fillestare
    int oldA = a;
    double oldB = b;

    // Shfaqje fillestare
    printf("\n--- Vlerat Fillestare ---\n");
    printf("a (direkt) = %d\n", a);
    printf("Adresa e a = %p\n", &a);
    printf("a nga pointer = %d\n", *pA);

    printf("\nb (direkt) = %.2lf\n", b);
    printf("Adresa e b = %p\n", &b);
    printf("b nga pointer = %.2lf\n", *pB);

    // Ndryshimi përmes pointer-it
    *pA = *pA + 10;
    *pB = *pB * 2;

    // Shfaqje pas ndryshimit
    printf("\n--- Pas Ndryshimit ---\n");
    printf("a = %d\n", a);
    printf("b = %.2lf\n", b);

    // Kontroll me if/else për a
    printf("\n--- Analiza per a ---\n");
    if (a > oldA) {
        printf("Vlera e a eshte rritur\n");
    } else if (a < oldA) {
        printf("Vlera e a eshte zvogeluar\n");
    } else {
        printf("Vlera e a ka mbetur e njejte\n");
    }

    // Kontroll intervali për b
    printf("\n--- Analiza per b ---\n");
    if (b >= 0 && b <= 100) {
        printf("b eshte ne intervalin [0, 100]\n");
    } else {
        printf("b eshte jashte intervalit [0, 100]\n");
    }

    return 0;
}
