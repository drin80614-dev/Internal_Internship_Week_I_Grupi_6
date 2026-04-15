#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int rezultati;

    printf("Shkruaj rezultatin nga 0 deri ne 100: ");
    scanf("%d", &rezultati);

    if (rezultati < 0 || rezultati > 100) {
        printf("Input-i nuk eshte valid.\n");
    }
    else if (rezultati >= 90) {
        printf("Vleresimi: Shkelqyeshem\n");
    }
    else if (rezultati >= 75) {
        printf("Vleresimi: Shume mire\n");
    }
    else if (rezultati >= 60) {
        printf("Vleresimi: Mire\n");
    }
    else {
        printf("Vleresimi: Ne permiresim\n");
    }

    return 0;
}