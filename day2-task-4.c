#include <stdio.h>

int main() {
    // Declare variables
    int age;
    char initial;
    double points;
    int workshopOption;

    // 1. Read input from user
    printf("=== Workshop Registration ===\n");
    printf("Enter your age (int): ");
    scanf("%d", &age);

    printf("Enter the first letter of your name (char): ");
    scanf(" %c", &initial);  // space before %c to catch any leftover newline

    printf("Enter your preliminary points (double, e.g. 68.5): ");
    scanf("%lf", &points);

    printf("Choose a workshop (1 = Basic, 2 = Intermediate, 3 = Advanced): ");
    scanf("%d", &workshopOption);

    // 2. Check age limit for participation (simple rule: age between 18 and 60)
    printf("\n--- Registration Summary ---\n");
    if (age >= 18 && age <= 60) {
        printf("Age check: %d years old -> Valid for participation.\n", age);
    } else {
        printf("Age check: %d years old -> NOT within the recommended limit (18–60).\n", age);
    }

    // 3. Classify student based on preliminary points using if / else if / else
    printf("Points: %.2lf -> ", points);
    if (points < 50) {
        printf("Classification: Needs more exercise (Nevojitet më shumë ushtrim)\n");
    } else if (points >= 50 && points <= 75) {
        printf("Classification: Ready to continue (Gati për vazhdim)\n");
    } else {  // points > 75
        printf("Classification: Ready for challenge (Gati për sfidë)\n");
    }

    // 4. Use switch to print the selected workshop name
    printf("Selected workshop: ");
    switch (workshopOption) {
        case 1:
            printf("Basic Workshop\n");
            break;
        case 2:
            printf("Intermediate Workshop\n");
            break;
        case 3:
            printf("Advanced Workshop\n");
            break;
        default:
            printf("Invalid option (only 1, 2 or 3 are allowed)\n");
    }

    // 5. Final summary line with initial and other info
    printf("\nParticipant '%c' (age %d) with %.2lf points.\n", initial, age, points);

    return 0;
}