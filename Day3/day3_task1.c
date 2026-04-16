#include <stdio.h>

int main() {
    int n, choice;

    printf("Enter size (1-12): ");
    scanf("%d", &n);

    if(n < 1 || n > 12) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Choose pattern:\n");
    printf("1 - Stars\n");
    printf("2 - Numbers\n");
    scanf("%d", &choice);

    if(choice == 1) {
        // Pattern me yje
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= i; j++) {
                printf("* ");
            }
            printf("\n");
        }
    }
    else if(choice == 2) {
        // Pattern me numra
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= i; j++) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    else {
        printf("Invalid choice\n");
    }

    return 0;
}