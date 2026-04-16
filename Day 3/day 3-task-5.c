#include <stdio.h>

// Define an enum with at least four clear values
enum StudentLevel {
    BEGINNER = 1,
    INTERMEDIATE,
    ADVANCED,
    EXPERT
};

int main() {
    int choice;
    int validCount = 0;
    int invalidCount = 0;
    enum StudentLevel level;

    printf("=== Student Level Evaluator ===\n");
    printf("This program will ask 3 users (or 3 test cases) to choose their level.\n\n");

    // For loop to handle three consecutive choices
    for (int i = 1; i <= 3; i++) {
        printf("User %d - Enter your level (1=Beginner, 2=Intermediate, 3=Advanced, 4=Expert): ", i);
        scanf("%d", &choice);

        // Link the numeric choice to the enum value
        switch (choice) {
            case BEGINNER:
                level = BEGINNER;
                printf("  -> Beginner: Keep practicing, you will improve soon!\n");
                validCount++;
                break;
            case INTERMEDIATE:
                level = INTERMEDIATE;
                printf("  -> Intermediate: Good progress, keep going!\n");
                validCount++;
                break;
            case ADVANCED:
                level = ADVANCED;
                printf("  -> Advanced: You know a lot, now focus on projects.\n");
                validCount++;
                break;
            case EXPERT:
                level = EXPERT;
                printf("  -> Expert: Excellent! Help others and master advanced topics.\n");
                validCount++;
                break;
            default:
                printf("  -> Invalid choice! Please enter a number between 1 and 4.\n");
                invalidCount++;
                break;
        }
        printf("\n");
    }

    // Display statistics at the end
    printf("=== Final Statistics ===\n");
    printf("Total valid choices:   %d\n", validCount);
    printf("Total invalid choices: %d\n", invalidCount);
    printf("Thank you for using the program.\n");

    return 0;
}