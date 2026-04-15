#include <stdio.h>

int main() {
    int day;

    printf("Shkruaj nje numer nga 1 deri ne 7: ");
    scanf("%d", &day);

    switch(day) {
        case 1:
            printf("E Hene - Dite pune\n");
            break;
        case 2:
            printf("E Marte - Dite pune\n");
            break;
        case 3:
            printf("E Merkure - Dite pune\n");
            break;
        case 4:
            printf("E Enjte - Dite pune\n");
            break;
        case 5:
            printf("E Premte - Dite pune\n");
            break;
        case 6:
            printf("E Shtune - Fundjave\n");
            break;
        case 7:
            printf("E Diele - Fundjave\n");
            break;
        default:
            printf("Input jo valid!\n");
    }

    return 0;
}