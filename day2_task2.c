#include <stdio.h>

int main() {
    int score;

    printf("Enter your result (0-100): ");
    scanf("%d", &score);

    if(score < 0 || score > 100) {
        printf("Invalid input\n");
    } 
    else if(score >= 90) {
        printf("Excellent\n");
    } 
    else if(score >= 75) {
        printf("Very Good\n");
    } 
    else if(score >= 60) {
        printf("Good\n");
    } 
    else {
        printf("Needs Improvement\n");
    }

    return 0;
}