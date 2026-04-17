struct Progres {
    int id;
    char emri[50];
    int pike;
    float nota;
    Status status;
};

lista[count].id = count + 1;

void kerko(struct Progres lista[], int count) {
    if (count == 0) {
        printf("Nuk ka regjistrime!\n");
        return;
    }

    int zgjedhja;
    printf("\nKerko sipas:\n");
    printf("1. ID\n");
    printf("2. Emrit\n");
    printf("Zgjedhja: ");
    scanf("%d", &zgjedhja);

    int found = 0;

    switch(zgjedhja) {

        case 1: {
            int id;
            printf("Shkruaj ID: ");
            scanf("%d", &id);

            for (int i = 0; i < count; i++) {
                if (lista[i].id == id) {
                    found = 1;

                    printf("\n--- REZULTATI ---\n");
                    printf("ID: %d\n", lista[i].id);
                    printf("Emri: %s\n", lista[i].emri);
                    printf("Nota: %.2f\n", lista[i].nota);
                    printf("Status: ");
                    printStatus(lista[i].status);
                    printf("\n");

                    // 🔸 VLERËSIM ME KUSHTE TË KOMBINUARA
                    if (lista[i].nota < 5 && lista[i].status != PERFUNDUAR) {
                        printf("Paralajmerim: Performanca e ulet dhe nuk eshte perfunduar!\n");
                    } else if (lista[i].nota >= 9 && lista[i].status == PERFUNDUAR) {
                        printf("Shkelqyeshem! Rezultat i larte dhe i perfunduar.\n");
                    } else if (lista[i].nota >= 7 && lista[i].status == NE_PROGRES) {
                        printf("Mire, por ende ne progres - vazhdo keshtu!\n");
                    } else {
                        printf("Gjendje normale.\n");
                    }
                }
            }
            break;
        }

        case 2: {
            char emri[50];
            printf("Shkruaj emrin: ");
            scanf(" %[^\n]", emri);

            for (int i = 0; i < count; i++) {
                if (strcmp(lista[i].emri, emri) == 0) {
                    found = 1;

                    printf("\n--- REZULTATI ---\n");
                    printf("ID: %d\n", lista[i].id);
                    printf("Emri: %s\n", lista[i].emri);
                    printf("Nota: %.2f\n", lista[i].nota);
                    printf("Status: ");
                    printStatus(lista[i].status);
                    printf("\n");

                    // 🔸 E NJËJTA LOGJIKË VLERËSIMI
                    if (lista[i].nota < 5 && lista[i].status != PERFUNDUAR) {
                        printf("Paralajmerim: Performanca e ulet dhe nuk eshte perfunduar!\n");
                    } else if (lista[i].nota >= 9 && lista[i].status == PERFUNDUAR) {
                        printf("Shkelqyeshem! Rezultat i larte dhe i perfunduar.\n");
                    } else if (lista[i].nota >= 7 && lista[i].status == NE_PROGRES) {
                        printf("Mire, por ende ne progres - vazhdo keshtu!\n");
                    } else {
                        printf("Gjendje normale.\n");
                    }
                }
            }
            break;
        }

        default:
            printf("Zgjedhje e pavlefshme!\n");
    }

    if (!found) {
        printf("Asnje regjistrim nuk u gjet!\n");
    }
}

printf("4. Kerko regjistrim\n");

case 4:
    kerko(lista, count);
    break;
