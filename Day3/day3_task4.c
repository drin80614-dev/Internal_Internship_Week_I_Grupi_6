#include <stdio.h>

int main() {
    int numri;
    float nota;

    int *pNumri;
    float *pNota;

    int paraNdryshimit;

    printf("Shkruaj nje numer te plote: ");
    scanf("%d", &numri);

    printf("Shkruaj nje numer me presje: ");
    scanf("%f", &nota);

    pNumri = &numri;
    pNota = &nota;

    printf("\n--- Vlerat fillestare ---\n");
    printf("Vlera direkte e numri: %d\n", numri);
    printf("Adresa e numri: %p\n", (void*)&numri);
    printf("Vlera permes pointer-it pNumri: %d\n", *pNumri);

    printf("\nVlera direkte e nota: %.2f\n", nota);
    printf("Adresa e nota: %p\n", (void*)&nota);
    printf("Vlera permes pointer-it pNota: %.2f\n", *pNota);

    paraNdryshimit = *pNumri;

    *pNumri = *pNumri + 10;

    printf("\n--- Pas ndryshimit me pointer ---\n");
    printf("Vlera e numri para ndryshimit: %d\n", paraNdryshimit);
    printf("Vlera e numri pas ndryshimit: %d\n", numri);

    if (numri > paraNdryshimit) {
        printf("Rezultati: Vlera eshte rritur.\n");
    } else if (numri < paraNdryshimit) {
        printf("Rezultati: Vlera eshte zvogeluar.\n");
    } else if (numri >= 0 && numri <= 20) {
        printf("Rezultati: Vlera ka mbetur e njejte dhe eshte ne intervalin 0 deri 20.\n");
    } else {
        printf("Rezultati: Vlera ka mbetur e njejte.\n");
    }

    return 0;
}