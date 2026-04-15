#include <stdio.h>

int main() {
    int age;
    char initial;
    float height;
    double average;

    short birthYear = 2007;
    long population = 1800000;

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your initial: ");
    scanf(" %c", &initial);

    printf("Enter your height (in meters): ");
    scanf("%f", &height);

    printf("Enter your average grade: ");
    scanf("%lf", &average);

    printf("\n--- USER PROFILE ---\n");
    printf("Age: %d\n", age);
    printf("Initial: %c\n", initial);
    printf("Height: %.2f m\n", height);
    printf("Average grade: %.2lf\n", average);
    printf("Birth Year (short): %d\n", birthYear);
    printf("Population (long): %ld\n", population);

    return 0;
}