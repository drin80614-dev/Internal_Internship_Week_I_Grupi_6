#include <stdio.h>

int main() {
    int age, workshop;
    char initial;
    double points;

    // Input
    printf("Shkruaj moshen: ");
    scanf("%d", &age);

    printf("Shkruaj inicialin: ");
    scanf(" %c", &initial);

    printf("Shkruaj piket paraprake: ");
    scanf("%lf", &points);

    printf("Zgjedh punetorine (1-3): ");
    scanf("%d", &workshop);

    // Kontrolli i moshes
    if(age < 14 || age > 25) {
        printf("\nNuk jeni ne moshen e lejuar per pjesemarrje.\n");
    } else {
        printf("\nMosha eshte e vlefshme per pjesemarrje.\n");
    }

    // Klasifikimi me if/else
    if(points < 50) {
        printf("Statusi: Nevojitet me shume ushtrim\n");
    }
    else if(points < 80) {
        printf("Statusi: Gati per vazhdim\n");
    }
    else {
        printf("Statusi: Gati per sfide\n");
    }

    // Switch per punetorine
    printf("Punetoria e zgjedhur: ");
    switch(workshop) {
        case 1:
            printf("Programim bazik\n");
            break;
        case 2:
            printf("Databaza\n");
            break;
        case 3:
            printf("Web Development\n");
            break;
        default:
            printf("Zgjedhje jo valide\n");
    }

    // Output final
    printf("\n--- PERMBLEDHJE ---\n");
    printf("Mosha: %d\n", age);
    printf("Iniciali: %c\n", initial);
    printf("Piket: %.2lf\n", points);
    printf("Opsioni: %d\n", workshop);

    return 0;
}