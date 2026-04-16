#include <stdio.h>

int main() {
    int start, end;
    int sum3 = 0, count3 = 0;
    int sum5 = 0, count5 = 0;

    printf("Shkruani fillimin e intervalit: ");
    scanf("%d", &start);

    printf("Shkruani fundin e intervalit: ");
    scanf("%d", &end);

    // Kontrolli i input-it
    if (start > end) {
        printf("Gabim: Fillimi duhet te jete me i vogel se fundi.\n");
        return 1;
    }

    // Loop për analizë
    for (int i = start; i <= end; i++) {
        if (i % 3 == 0) {
            sum3 += i;
            count3++;
        }
        else if (i % 5 == 0 && i % 3 != 0) {
            sum5 += i;
            count5++;
        }
    }

    // Rezultatet
    printf("\nNumrat qe pjestohet me 3: %d\n", count3);
    printf("Shuma e tyre: %d\n", sum3);

    printf("\nNumrat qe pjestohet me 5 (jo me 3): %d\n", count5);
    printf("Shuma e tyre: %d\n", sum5);

    // Krahasimi
    if (sum3 > sum5) {
        printf("\nShuma e numrave qe pjestohet me 3 eshte me e madhe.\n");
    }
    else if (sum5 > sum3) {
        printf("\nShuma e numrave qe pjestohet me 5 eshte me e madhe.\n");
    }
    else {
        printf("\nTe dy shumat jane te barabarta.\n");
    }

    return 0;
}