#include <stdio.h>
#include <string.h>

#define MAX 5  // kapaciteti maksimal

// Struktura për një regjistrim
struct Progres {
    char emri[50];
    int pike;
    float nota;
};

int main() {
    struct Progres lista[MAX];  // array i regjistrimeve
    int count = 0;              // sa regjistrime janë aktualisht
    int zgjedhja;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Shto regjistrim\n");
        printf("2. Shfaq te gjitha regjistrimet\n");
        printf("3. Dil\n");
        printf("Zgjedhja: ");
        scanf("%d", &zgjedhja);

        switch(zgjedhja) {

            case 1:
                if (count >= MAX) {
                    printf("Keni arritur maksimumin e regjistrimeve (%d)!\n", MAX);
                } else {
                    printf("Shkruaj emrin: ");
                    scanf(" %[^\n]", lista[count].emri);

                    printf("Shkruaj piket: ");
                    scanf("%d", &lista[count].pike);

                    printf("Shkruaj noten: ");
                    scanf("%f", &lista[count].nota);

                    count++;
                    printf("Regjistrimi u shtua me sukses!\n");
                }
                break;

            case 2:
                if (count == 0) {
                    printf("Nuk ka regjistrime!\n");
                } else {
                    printf("\n--- Lista e Regjistrimeve ---\n");
                    for (int i = 0; i < count; i++) {
                        printf("\nRegjistrimi %d:\n", i + 1);
                        printf("Emri: %s\n", lista[i].emri);
                        printf("Piket: %d\n", lista[i].pike);
                        printf("Nota: %.2f\n", lista[i].nota);
                    }
                }
                break;

            case 3:
                printf("Duke dale nga programi...\n");
                break;

            default:
                printf("Zgjedhje e pavlefshme!\n");
        }

    } while (zgjedhja != 3);

    return 0;
}
