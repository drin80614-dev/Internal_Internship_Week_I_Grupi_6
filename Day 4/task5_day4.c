void updateRegjistrim(struct Progres *r) {
    printf("\n--- UPDATE REGJISTRIMI ---\n");

    printf("Nota e re: ");
    scanf("%f", &r->nota);  // pointer përdoret këtu

    int s;
    do {
        printf("Statusi i ri (1.Filluar 2.Ne progres 3.Perfunduar): ");
        scanf("%d", &s);

        if (s >= 1 && s <= 3) {
            r->status = (Status)s;  // modifikim direkt
        } else {
            printf("Zgjedhje e pavlefshme!\n");
        }
    } while (s < 1 || s > 3);

    printf("Regjistrimi u perditesua!\n");
}

void updateByID(struct Progres lista[], int count) {
    if (count == 0) {
        printf("Nuk ka regjistrime!\n");
        return;
    }

    int id;
    printf("Shkruaj ID per update: ");
    scanf("%d", &id);

    int found = 0;

    for (int i = 0; i < count; i++) {
        if (lista[i].id == id) {
            found = 1;

            // dërgojmë ADRESËN (pointer)
            updateRegjistrim(&lista[i]);

            break;
        }
    }

    if (!found) {
        printf("Regjistrimi nuk u gjet!\n");
    }
}

printf("5. Update regjistrim\n");

case 5:
    updateByID(lista, count);
    break;
