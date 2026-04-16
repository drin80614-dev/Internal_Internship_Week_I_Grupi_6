#include <stdio.h>

int main() {
    // 1. Declaration of all required variable types
    int age;
    char initial;
    float height;
    double average;
    short shortValue;
    long longValue;

    // 2. Input from the user (int, char, float, double)
    printf("Enter your age (int): ");
    scanf("%d", &age);

    printf("Enter the first letter of your name (char): ");
    // Space before %c ignores any leftover newline from previous input
    scanf(" %c", &initial);

    printf("Enter your height in meters (float, e.g. 1.75): ");
    scanf("%f", &height);

    printf("Enter your average grade (double, e.g. 88.5): ");
    scanf("%lf", &average);

    // 3. Short and long values – assign them directly in code (they will be used in output)
    shortValue = 32000;      // typical short maximum
    longValue = 123456789L;  // L suffix indicates long constant

    // 4. Output – clear labels for each field
    printf("\n--- Your Profile ---\n");
    printf("Age (int)               : %d\n", age);
    printf("Initial (char)          : %c\n", initial);
    printf("Height (float)          : %.2f m\n", height);
    printf("Average grade (double)  : %.2lf\n", average);
    printf("Predefined short value  : %hd\n", shortValue);
    printf("Predefined long value   : %ld\n", longValue);

    return 0;
}
