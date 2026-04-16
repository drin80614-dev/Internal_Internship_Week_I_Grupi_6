
int main() {
    enum Level {BEGINNER = 1, INTERMEDIATE, ADVANCED, EXPERT};

    int choice;
    int validCount = 0, invalidCount = 0;

    for(int i = 1; i <= 3; i++) {
        printf("User %d - Choose level (1-4): ", i);
        scanf("%d", &choice);

        enum Level level = choice;

        switch(level) {
            case BEGINNER:
                printf("Beginner: You should practice the basics.\n");
                validCount++;
                break;
            case INTERMEDIATE:
                printf("Intermediate: You are making good progress.\n");
                validCount++;
                break;
            case ADVANCED:
                printf("Advanced: You are ready for harder tasks.\n");
                validCount++;
                break;
            case EXPERT:
                printf("Expert: You can solve complex problems.\n");
                validCount++;
                break;
            default:
                printf("Invalid choice.\n");
                invalidCount++;
        }

        printf("\n");
    }

    printf("--- STATISTICS ---\n");
    printf("Valid choices: %d\n", validCount);
    printf("Invalid choices: %d\n", invalidCount);

    return 0;
}