#include <stdio.h>

int main() {
    int day;

    printf("Enter a number (1–7): ");
    scanf("%d", &day);

    switch (day) {
        case 1:
            printf("Monday – Workday\n");
            break;
        case 2:
            printf("Tuesday – Workday\n");
            break;
        case 3:
            printf("Wednesday – Workday\n");
            break;
        case 4:
            printf("Thursday – Workday\n");
            break;
        case 5:
            printf("Friday – Workday\n");
            break;
        case 6:
            printf("Saturday – Weekend\n");
            break;
        case 7:
            printf("Sunday – Weekend\n");
            break;
        default:
            printf("Invalid input! Please enter a number between 1 and 7.\n");
    }

    return 0;
}