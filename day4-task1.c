#include <stdio.h>

#define MAX 5

// Enum për statusin
enum Status {
    FILLIMTAR = 1,
    MESATAR,
    AVANCUAR
};

// Struktura e regjistrimit
struct Progres {
    char emri[50];
    int mosha;
    float nota;
    enum Status status;
};

// Funksion për shfaqjen e statusit si tekst
void shfaqStatus(enum Status s) {

    switch(s) {
        case FILLIMTAR:
            printf("Fillimtar");
            break;

        case MESATAR:
            printf("Mesatar");
            break;

        case AVANCUAR:
            printf("Avancuar");
            break;

        default:
            printf("I panjohur");
    }
}

int main() {

    struct Progres regjistrime[MAX];

    int count = 0;
    int zgjedhja;

    do {

        printf("\n----- MENU KRYESORE -----\n");
        printf("1. Shto regjistrim\n");
        printf("2. Shfaq regjistrimet\n");
        printf("3. Dil\n");
        printf("Zgjedhja juaj: ");
        scanf("%d", &zgjedhja);

        switch(zgjedhja) {

        case 1:

            if(count >= MAX) {
                printf("Maksimumi i regjistrimeve (%d) eshte arritur.\n", MAX);
                break;
            }

            printf("Shkruaj emrin: ");
            scanf("%s", regjistrime[count].emri);

            printf("Shkruaj moshen: ");
            scanf("%d", &regjistrime[count].mosha);

            printf("Shkruaj noten: ");
            scanf("%f", &regjistrime[count].nota);

            // Zgjedhja e statusit me validim
            int statusInput;

            do {

                printf("\nZgjidh statusin:\n");
                printf("1. Fillimtar\n");
                printf("2. Mesatar\n");
                printf("3. Avancuar\n");
                printf("Zgjedhja: ");

                scanf("%d", &statusInput);

                switch(statusInput) {

                case 1:
                    regjistrime[count].status = FILLIMTAR;
                    break;

                case 2:
                    regjistrime[count].status = MESATAR;
                    break;

                case 3:
                    regjistrime[count].status = AVANCUAR;
                    break;

                default:
                    printf("Status i pavlefshem! Provo perseri.\n");
                }

            } while(statusInput < 1 || statusInput > 3);

            count++;

            printf("Regjistrimi u shtua me sukses!\n");

            break;

        case 2:

            if(count == 0) {
                printf("Nuk ka regjistrime.\n");
            }
            else {

                printf("\n--- LISTA E REGJISTRIMEVE ---\n");

                for(int i = 0; i < count; i++) {

                    printf("\nRegjistrimi %d:\n", i + 1);
                    printf("Emri: %s\n", regjistrime[i].emri);
                    printf("Mosha: %d\n", regjistrime[i].mosha);
                    printf("Nota: %.2f\n", regjistrime[i].nota);

                    printf("Statusi: ");
                    shfaqStatus(regjistrime[i].status);
                    printf("\n");
                }
            }

            break;

        case 3:
            printf("Programi u mbyll.\n");
            break;

        default:
            printf("Zgjedhje e pavlefshme! Provo perseri.\n");
        }

    } while(zgjedhja != 3);

    return 0;
}