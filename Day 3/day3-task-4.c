#include <stdio.h>

int main() {
    // 1. Declare two numeric variables
    int originalInt;
    double originalDouble;

    // 2. Declare pointers for each
    int *intPtr;
    double *doublePtr;

    // 3. Assign addresses using &
    intPtr = &originalInt;
    doublePtr = &originalDouble;

    // 4. Read initial values from user
    printf("=== Pointer Manipulation Program ===\n");
    printf("Enter an integer value: ");
    scanf("%d", &originalInt);
    printf("Enter a double value: ");
    scanf("%lf", &originalDouble);

    // Save copies to compare later (for increase/decrease check)
    int oldInt = originalInt;
    double oldDouble = originalDouble;

    // 5. Display direct values, addresses, and values via pointers
    printf("\n--- Before Changes ---\n");
    printf("Direct int value        : %d\n", originalInt);
    printf("Address of int          : %p\n", (void*)&originalInt);
    printf("Value via int pointer   : %d\n", *intPtr);

    printf("Direct double value     : %.2lf\n", originalDouble);
    printf("Address of double       : %p\n", (void*)&originalDouble);
    printf("Value via double pointer: %.2lf\n", *doublePtr);

    // 6. Modify the integer value through its pointer
    printf("\n--- Modifying integer via pointer ---\n");
    printf("Enter a new integer value to assign through pointer: ");
    int newInt;
    scanf("%d", &newInt);
    *intPtr = newInt;   // originalInt is now changed

    // 7. Modify the double value through its pointer
    printf("\n--- Modifying double via pointer ---\n");
    printf("Enter a new double value to assign through pointer: ");
    double newDouble;
    scanf("%lf", &newDouble);
    *doublePtr = newDouble;

    // 8. Display values after modification
    printf("\n--- After Changes ---\n");
    printf("Integer value after pointer modification: %d\n", originalInt);
    printf("Double value after pointer modification : %.2lf\n", originalDouble);

    // 9. If/else checks: compare with old values and classify ranges
    printf("\n--- Final Check ---\n");

    // Check for integer: increased, decreased, or same
    if (originalInt > oldInt) {
        printf("The integer value INCREASED from %d to %d.\n", oldInt, originalInt);
    } else if (originalInt < oldInt) {
        printf("The integer value DECREASED from %d to %d.\n", oldInt, originalInt);
    } else {
        printf("The integer value REMAINED THE SAME (%d).\n", originalInt);
    }

    // Check for double: increased, decreased, or same
    if (originalDouble > oldDouble) {
        printf("The double value INCREASED from %.2lf to %.2lf.\n", oldDouble, originalDouble);
    } else if (originalDouble < oldDouble) {
        printf("The double value DECREASED from %.2lf to %.2lf.\n", oldDouble, originalDouble);
    } else {
        printf("The double value REMAINED THE SAME (%.2lf).\n", originalDouble);
    }

    // Additional interval check for the final double value
    if (originalDouble > 100.0) {
        printf("The final double value is ABOVE 100.\n");
    } else if (originalDouble < 0.0) {
        printf("The final double value is NEGATIVE.\n");
    } else {
        printf("The final double value is BETWEEN 0 AND 100 (inclusive).\n");
    }

    return 0;
}