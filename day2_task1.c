#include <stdio.h>

int main() {
    int age;
    char initial;
    float height;
    double average;
    short year = 2024;
    long population = 1800000;

    printf("Mosha: ");
    scanf("%d", &age);

    printf("Iniciali: ");
    scanf(" %c", &initial);

    printf("Gjatesia: ");
    scanf("%f", &height);

    printf("Mesatarja: ");
    scanf("%lf", &average);

    printf("\n--- PROFILI ---\n");
    printf("Mosha: %d\n", age);
    printf("Iniciali: %c\n", initial);
    printf("Gjatesia: %f\n", height);
    printf("Mesatarja: %lf\n", average);
    printf("Viti: %hd\n", year);
    printf("Popullsia: %ld\n", population);

    return 0;
}