#include <stdio.h>

int main() {
    int numri;
    double vlera, vlera_para;
    int *pNumri;
    double *pVlera;

    // lidhja e pointerave me variablat
    pNumri = &numri;
    pVlera = &vlera;

    // marrja e input-it
    printf("Shkruaj nje numer integer: ");
    scanf("%d", &numri);

    printf("Shkruaj nje numer double: ");
    scanf("%lf", &vlera);

    // ruajme vleren para ndryshimit
    vlera_para = *pVlera;

    // shfaqja e vlerave direkte, adresave dhe vlerave permes pointerit
    printf("\n--- TE DHENAT FILLESTARE ---\n");
    printf("Numri direkt: %d\n", numri);
    printf("Adresa e numrit: %p\n", (void*)pNumri);
    printf("Numri permes pointerit: %d\n", *pNumri);

    printf("Vlera direkte: %.2lf\n", vlera);
    printf("Adresa e vleres: %p\n", (void*)pVlera);
    printf("Vlera permes pointerit: %.2lf\n", *pVlera);

    // ndryshimi i vlerave permes pointerave
    *pNumri = *pNumri + 5;
    *pVlera = *pVlera * 2;

    // shfaqja pas ndryshimit
    printf("\n--- PAS NDRYSHIMIT ME POINTER ---\n");
    printf("Numri i ri: %d\n", numri);
    printf("Vlera para ndryshimit: %.2lf\n", vlera_para);
    printf("Vlera pas ndryshimit: %.2lf\n", vlera);

    // kontrolli me if/else
    printf("\n--- KONTROLLI PERFUNDIMTAR ---\n");
    if (vlera > vlera_para) {
        printf("Vlera perfundimtare eshte rritur.\n");
    } else if (vlera < vlera_para) {
        printf("Vlera perfundimtare eshte zvogeluar.\n");
    } else {
        printf("Vlera perfundimtare ka mbetur e njejte.\n");
    }

    // kontroll shtese per interval
    if (vlera >= 0 && vlera <= 100) {
        printf("Vlera perfundimtare hyn ne intervalin [0, 100].\n");
    } else {
        printf("Vlera perfundimtare nuk hyn ne intervalin [0, 100].\n");
    }

    return 0;
}