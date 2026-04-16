#include <stdio.h>

int main() {
    int n, choice;

    // Marrja e input-it
    printf("Shkruaj nje numer (1 - 12): ");
    scanf("%d", &n);

    // Validimi i input-it
    if (n < 1 || n > 12) {
        printf("Input i pavlefshem! Duhet te jete nga 1 deri ne 12.\n");
        return 0;
    }

    // Zgjedhja e pattern-it
    printf("Zgjidh pattern-in:\n");
    printf("1 - Me yje (*)\n");
    printf("2 - Me numra\n");
    printf("Zgjedhja: ");
    scanf("%d", &choice);

    printf("\n");

    // Pattern me yje
    if (choice == 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                printf("* ");
            }
            printf("\n");
        }
    }
    // Pattern me numra
    else if (choice == 2) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    else {
        printf("Zgjedhje e pavlefshme!\n");
    }

    return 0;
}
