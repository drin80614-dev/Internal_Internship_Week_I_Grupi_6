#include <stdio.h>

int main() {
    // Deklarimi i variablave
    int age;
    char initial;
    float height;
    double average;

    short year = 2026;      // vlerë e caktuar në kod
    long population = 1800000;  // vlerë e caktuar në kod

    // Marrja e input-it
    printf("Shkruaj moshen: ");
    scanf("%d", &age);

    printf("Shkruaj inicialin: ");
    scanf(" %c", &initial);  // hapësirë para %c per me shmang problem

    printf("Shkruaj gjatesine (ne metra): ");
    scanf("%f", &height);

    printf("Shkruaj mesataren: ");
    scanf("%lf", &average);

    // Output
    printf("\n--- PROFILI I PERDORUESIT ---\n");
    printf("Mosha: %d\n", age);
    printf("Iniciali: %c\n", initial);
    printf("Gjatesia: %.2f m\n", height);
    printf("Mesatarja: %.2lf\n", average);
    printf("Viti (short): %d\n", year);
    printf("Popullsia (long): %ld\n", population);

    return 0;
}