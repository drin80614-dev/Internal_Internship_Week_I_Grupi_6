#include <stdio.h>

int main() {
    int score;

    // Get input from user
    printf("Enter your score (0–100): ");
    scanf("%d", &score);

    // Validate input
    if (score < 0 || score > 100) {
        printf("Invalid input! Score must be between 0 and 100.\n");
    }
    // Classify from highest to lowest
    else if (score >= 90) {
        printf("Rating: Excellent (Shkëlqyeshëm)\n");
    }
    else if (score >= 75) {
        printf("Rating: Very good (Shumë mirë)\n");
    }
    else if (score >= 60) {
        printf("Rating: Good (Mirë)\n");
    }
    else {
        printf("Rating: Needs improvement (Në përmirësim)\n");
    }

    return 0;
}
