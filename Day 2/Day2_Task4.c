#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int mosha;
    char iniciali;
    double pikeParaprake;
    int opsioni;

    printf("Shkruaj moshen: ");
    scanf("%d", &mosha);

    printf("Shkruaj inicialin: ");
    scanf(" %c", &iniciali);

    printf("Shkruaj piket paraprake: ");
    scanf("%lf", &pikeParaprake);

    printf("Zgjedh punetorine (1, 2 ose 3): ");
    scanf("%d", &opsioni);

    printf("\n--- Permbledhja e Regjistrimit ---\n");
    printf("Mosha: %d\n", mosha);
    printf("Iniciali: %c\n", iniciali);
    printf("Piket paraprake: %.2lf\n", pikeParaprake);

    if (mosha >= 14 && mosha <= 18) {
        printf("Pjesemarrja sipas moshes: Lejohet\n");
    }
    else {
        printf("Pjesemarrja sipas moshes: Nuk lejohet\n");
    }

    if (pikeParaprake < 50) {
        printf("Vleresimi: Nevojitet me shume ushtrim\n");
    }
    else if (pikeParaprake < 80) {
        printf("Vleresimi: Gati per vazhdim\n");
    }
    else {
        printf("Vleresimi: Gati per sfide\n");
    }

    switch (opsioni) {
    case 1:
        printf("Punetoria e zgjedhur: Programim Bazik\n");
        break;
    case 2:
        printf("Punetoria e zgjedhur: Algoritme\n");
        break;
    case 3:
        printf("Punetoria e zgjedhur: Zgjidhje Problemesh\n");
        break;
    default:
        printf("Punetoria e zgjedhur: Opsion i pavlefshem\n");
        break;
    }

    return 0;
}