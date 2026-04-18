#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5
#define NAME_LEN 50

enum Status { PASSING, NEEDS_IMPROVEMENT, AT_RISK };

struct Student {
    int id;
    char name[NAME_LEN];
    float score;
    enum Status status;
};

// Funksion që përdor POINTER për të modifikuar rezultatin dhe statusin
void updateStudentScore(struct Student *student, float newScore) {
    printf("\n--- BEFORE UPDATE ---\n");
    printf("Adresa e studentit (pointer): %p\n", (void*)student);
    printf("Vlera e vjeter e score: %.2f\n", student->score);
    printf("Statusi i vjeter: %s\n", (student->status == PASSING) ? "Passing" : "Other");

    // Modifikimi direkt përmes pointer-it
    student->score = newScore;
    if (newScore >= 70)
        student->status = PASSING;
    else
        student->status = NEEDS_IMPROVEMENT;

    printf("\n--- AFTER UPDATE ---\n");
    printf("Vlera e re e score: %.2f\n", student->score);
    printf("Statusi i ri: %s\n", (student->status == PASSING) ? "Passing" : "Needs Improvement");
    printf("Ndryshimi mbetet në strukturën origjinale.\n");
}

int main() {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    // Shtojmë një student shembull
    students[count].id = 1;
    strcpy(students[count].name, "Test Student");
    students[count].score = 65.0;
    students[count].status = NEEDS_IMPROVEMENT;
    count++;

    do {
        printf("\n===== POINTER DEMO =====\n");
        printf("1. Shfaq te dhenat e studentit\n");
        printf("2. Ndrysho rezultatin duke perdorur POINTER\n");
        printf("3. Dil\n");
        printf("Zgjedhja juaj: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nID: %d | Emri: %s | Score: %.2f | Status: %s\n",
                       students[0].id, students[0].name, students[0].score,
                       (students[0].status == PASSING) ? "Passing" : "Needs Improvement");
                break;
            case 2: {
                float newScore;
                printf("\nShkruani rezultatin e ri (0-100): ");
                scanf("%f", &newScore);
                // KALOJME ADRESEN E STUDENTIT (pointer) ne funksion
                updateStudentScore(&students[0], newScore);
                break;
            }
            case 3:
                printf("Dalje.\n");
                break;
            default:
                printf("Zgjedhje e pavlefshme.\n");
        }
    } while (choice != 3);

    return 0;
}