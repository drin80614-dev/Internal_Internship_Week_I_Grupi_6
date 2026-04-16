#include <stdio.h>

int main() {
    int start, end;
    int evenCount = 0, oddCount = 0;
    int evenSum = 0, oddSum = 0;

    printf("Enter start of interval: ");
    scanf("%d", &start);

    printf("Enter end of interval: ");
    scanf("%d", &end);

    if (start > end) {
        printf("Invalid interval! Start must be less than or equal to end.\n");
        return 0;
    }

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

    printf("\nInterval: %d to %d\n", start, end);
    printf("Total numbers: %d\n", total);
    printf("Even numbers: %d, Sum: %d\n", evenCount, evenSum);
    printf("Odd numbers: %d, Sum: %d\n", oddCount, oddSum);

    if (evenCount > oddCount) {
        printf("More even numbers.\n");
    } else if (oddCount > evenCount) {
        printf("More odd numbers.\n");
    } else {
        printf("Equal number of even and odd numbers.\n");
    }

    return 0;
}
