#include <stdio.h>

int main() {
    int start, end;
    int count3 = 0, count5 = 0;
    int sum3 = 0, sum5 = 0;

    printf("Shkruaj fillimin e intervalit: ");
    scanf("%d", &start);

    printf("Shkruaj fundin e intervalit: ");
    scanf("%d", &end);

    // Validim
    if (start > end) {
        printf("Interval i pavlefshem!\n");
        return 0;
    }

    // Loop
    for (int i = start; i <= end; i++) {
        if (i % 3 == 0) {
            count3++;
            sum3 += i;
        }
        else if (i % 5 == 0) {
            count5++;
            sum5 += i;
        }
    }

    printf("\nRezultatet:\n");
    printf("Numra qe pjesetohen me 3: %d\n", count3);
    printf("Shuma e tyre: %d\n", sum3);

    printf("\nNumra qe pjesetohen me 5 (jo me 3): %d\n", count5);
    printf("Shuma e tyre: %d\n", sum5);

    // Krahasimi
    if (sum3 > sum5) {
        printf("\nShuma e numrave qe pjesetohen me 3 eshte me e madhe.\n");
    } else if (sum5 > sum3) {
        printf("\nShuma e numrave qe pjesetohen me 5 eshte me e madhe.\n");
    } else {
        printf("\nShumat jane te barabarta.\n");
    }

    return 0;
}