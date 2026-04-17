#include <stdio.h>
#include <string.h>

#define MAX 5

// Enum për statusin
typedef enum {
    FILLUAR = 1,
    NE_PROGRES,
    PERFUNDUAR
} Status;

// Struktura
struct Progres {
    char emri[50];
    int pike;
    float nota;
    Status status;  // lidhja direkte me enum
};

// Funksion për me shfaq statusin si tekst
void printStatus(Status s) {
    switch(s) {
        case FILLUAR: printf("Filluar"); break;
        case NE_PROGRES: printf("Ne progres"); break;
        case PERFUNDUAR: printf("Perfunduar"); break;
        default: printf("I panjohur");
    }
}

int main() {
    struct Progres lista[MAX];
    int count = 0;
    int zgjedhja;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Shto regjistrim\n");
        printf("2. Shfaq te gjitha\n");
        printf("3. Dil\n");
        printf("Zgjedhja: ");

        if (scanf("%d", &zgjedhja) != 1) {
            printf("Input i pavlefshem!\n");
            while(getchar() != '\n'); // pastrim buffer
            continue;
        }

        switch(zgjedhja) {

            case 1:
                if (count >= MAX) {
                    printf("Keni arritur maksimumin (%d)!\n", MAX);
                    break;
                }

                printf("Emri: ");
                scanf(" %[^\n]", lista[count].emri);

                printf("Piket: ");
                if (scanf("%d", &lista[count].pike) != 1) {
                    printf("Piket duhet te jene numer!\n");
                    while(getchar() != '\n');
                    break;
                }

                printf("Nota: ");
                if (scanf("%f", &lista[count].nota) != 1) {
                    printf("Nota duhet te jete numer!\n");
                    while(getchar() != '\n');
                    break;
                }

                // Zgjedhja e statusit me validim
                int s;
                do {
                    printf("Zgjidh statusin:\n");
                    printf("1. Filluar\n");
                    printf("2. Ne progres\n");
                    printf("3. Perfunduar\n");
                    printf("Zgjedhja: ");

                    if (scanf("%d", &s) != 1) {
                        printf("Input i pavlefshem!\n");
                        while(getchar() != '\n');
                        s = 0;
                        continue;
                    }

                    switch(s) {
                        case FILLUAR:
                        case NE_PROGRES:
                        case PERFUNDUAR:
                            lista[count].status = (Status)s;
                            break;
                        default:
                            printf("Status i pavlefshem! Provo perseri.\n");
                    }

                } while (s < 1 || s > 3);

                count++;
                printf("Regjistrimi u shtua!\n");
                break;

            case 2:
                if (count == 0) {
                    printf("Nuk ka regjistrime!\n");
                } else {
                    printf("\n--- Lista ---\n");
                    for (int i = 0; i < count; i++) {
                        printf("\nRegjistrimi %d\n", i + 1);
                        printf("Emri: %s\n", lista[i].emri);
                        printf("Piket: %d\n", lista[i].pike);
                        printf("Nota: %.2f\n", lista[i].nota);
                        printf("Status: ");
                        printStatus(lista[i].status);
                        printf("\n");
                    }
                }
                break;

            case 3:
                printf("Duke dale...\n");
                break;

            default:
                printf("Zgjedhje e pavlefshme! Provo perseri.\n");
        }

    } while (zgjedhja != 3);

    return 0;
}
