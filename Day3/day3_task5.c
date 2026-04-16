#include <stdio.h>

// enum me 4 vlera
enum Nivel {
    FILLESTAR = 1,
    MESATAR,
    I_AVANCUAR,
    EKSPERT
};

int main() {
    int zgjedhje;
    int valid = 0, invalid = 0;

    // loop për 3 raste testimi
    for(int i = 1; i <= 3; i++) {
        printf("\nRasti %d\n", i);
        printf("Zgjidh nivelin (1-Fillestar, 2-Mesatar, 3-I avancuar, 4-Ekspert): ");
        scanf("%d", &zgjedhje);

        switch(zgjedhje) {
            case FILLESTAR:
                printf("Je fillestar, duhet me shume ushtrim.\n");
                valid++;
                break;
            case MESATAR:
                printf("Je ne nivel mesatar, vazhdo keshtu.\n");
                valid++;
                break;
            case I_AVANCUAR:
                printf("Je i avancuar, gati per sfida.\n");
                valid++;
                break;
            case EKSPERT:
                printf("Je ekspert, shume mire!\n");
                valid++;
                break;
            default:
                printf("Input i pavlefshem!\n");
                invalid++;
        }
    }

    // statistikat
    printf("\n--- Statistikat ---\n");
    printf("Zgjedhje valide: %d\n", valid);
    printf("Zgjedhje invalide: %d\n", invalid);

    return 0;
}