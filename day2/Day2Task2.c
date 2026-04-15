#include <stdio.h>

int main() {
    int result;

    printf("Shkruaj rezultatin (0-100): ");
    scanf("%d", &result);

    // Kontrolli i intervalit
    if(result < 0 || result > 100) {
        printf("Input jo valid!\n");
    }
    // Klasifikimi
    else if(result >= 90) {
        printf("Vleresimi: Shkelqyeshem\n");
    }
    else if(result >= 75) {
        printf("Vleresimi: Shume mire\n");
    }
    else if(result >= 60) {
        printf("Vleresimi: Mire\n");
    }
    else {
        printf("Vleresimi: Ne permiresim\n");
    }

    return 0;
}