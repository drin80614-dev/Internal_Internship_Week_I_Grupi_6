#include <stdio.h>

int main() {
    int age, option;
    char initial;
    double points;

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your initial: ");
    scanf(" %c", &initial);

    printf("Enter your previous points: ");
    scanf("%lf", &points);

    printf("Choose workshop (1-3): ");
    scanf("%d", &option);

    // Kontroll moshe
    if(age < 15 || age > 25) {
        printf("You are not eligible to participate.\n");
    } else {
        printf("You are eligible to participate.\n");
    }

    // Klasifikimi me if/else
    if(points < 50) {
        printf("Level: Needs more practice\n");
    } 
    else if(points < 80) {
        printf("Level: Ready to continue\n");
    } 
    else {
        printf("Level: Ready for challenge\n");
    }

    // Zgjedhja me switch
    printf("Workshop: ");
    switch(option) {
        case 1:
            printf("Programming Basics\n");
            break;
        case 2:
            printf("Web Development\n");
            break;
        case 3:
            printf("Data Analysis\n");
            break;
        default:
            printf("Invalid option\n");
    }

    // Përmbledhja
    printf("\n--- SUMMARY ---\n");
    printf("Age: %d\n", age);
    printf("Initial: %c\n", initial);
    printf("Points: %.2lf\n", points);
    printf("Option chosen: %d\n", option);

    return 0;
}