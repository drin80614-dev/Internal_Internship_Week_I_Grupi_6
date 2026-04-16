#include <stdio.h>

int main() {
    int start, end;
    int evenCount = 0, oddCount = 0;
    int evenSum = 0, oddSum = 0;

    printf("Shkruaj vleren fillestare: ");
    scanf("%d", &start);

    printf("Shkruaj vleren perfundimtare: ");
    scanf("%d", &end);

    // Validim
    if (start > end) {
        printf("Interval i pavlefshem!\n");
        return 0;
    }

    // Loop
    for (int i = start; i <= end; i++) {
        if (i % 2 == 0) {
            evenCount++;
            evenSum += i;
        } else {
            oddCount++;
            oddSum += i;
        }
    }

    int total = end - start + 1;

    printf("\nIntervali: %d - %d\n", start, end);
    printf("Totali i numrave: %d\n", total);

    printf("\nNumra çift: %d\n", evenCount);
    printf("Shuma e numrave çift: %d\n", evenSum);

    printf("\nNumra tek: %d\n", oddCount);
    printf("Shuma e numrave tek: %d\n", oddSum);

    if (evenCount > oddCount) {
        printf("\nKa me shume numra çift.\n");
    } else if (oddCount > evenCount) {
        printf("\nKa me shume numra tek.\n");
    } else {
        printf("\nNumrat çift dhe tek jane te barabarte.\n");
    }

    return 0;
}