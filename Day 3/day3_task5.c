#include <stdio.h>

// Krijimi i enum
enum Level {
    BEGINNER = 1,
    INTERMEDIATE,
    ADVANCED,
    EXPERT
};

int main() {
    int choice;
    int validCount = 0, invalidCount = 0;

    // for loop për 3 raste
    for (int i = 1; i <= 3; i++) {
        printf("\nZgjedhja %d\n", i);
        printf("Zgjidh nivelin (1-BEGINNER, 2-INTERMEDIATE, 3-ADVANCED, 4-EXPERT): ");
        scanf("%d", &choice);

        switch (choice) {
            case BEGINNER:
                printf("Ti je fillestar. Fillo me ushtrime bazike.\n");
                validCount++;
                break;

            case INTERMEDIATE:
                printf("Ti je mesatar. Mund te provosh sfida me te veshtira.\n");
                validCount++;
                break;

            case ADVANCED:
                printf("Ti je i avancuar. Je ne rruge shume te mire.\n");
                validCount++;
                break;

            case EXPERT:
                printf("Ti je ekspert. Mund te ndihmosh te tjeret.\n");
                validCount++;
                break;

            default:
                printf("Input i pavlefshem! Zgjidh numer nga 1 deri 4.\n");
                invalidCount++;
        }
    }

    // Statistikat
    printf("\n--- Statistikat ---\n");
    printf("Zgjedhje valide: %d\n", validCount);
    printf("Zgjedhje invalide: %d\n", invalidCount);

    return 0;
}
