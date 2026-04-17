#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

// Enum for student status
enum Status {
    PASSING,
    NEEDS_IMPROVEMENT,
    AT_RISK,
    NOT_EVALUATED
};

// Student structure
struct Student {
    int id;
    char name[NAME_LEN];
    float score;
    enum Status status;
};

// Function prototypes
void printMenu();
void addStudent(struct Student students[], int *count);
void displayAllStudents(const struct Student students[], int count);
const char* statusToString(enum Status s);
enum Status determineStatus(float score);
int isValidScore(float score);
void updateStudentScore(struct Student *student, float newScore); // uses pointer

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                if (studentCount < MAX_STUDENTS)
                    addStudent(students, &studentCount);
                else
                    printf("Cannot add more students. Maximum limit of %d reached.\n", MAX_STUDENTS);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    } while (choice != 3);

    return 0;
}

void printMenu() {
    printf("\n===== Student Progress Tracker =====\n");
    printf("1. Add a new student record\n");
    printf("2. Display all students\n");
    printf("3. Exit\n");
    printf("===================================\n");
}

int isValidScore(float score) {
    return (score >= 0.0 && score <= 100.0);
}

enum Status determineStatus(float score) {
    if (score >= 70.0)
        return PASSING;
    else if (score >= 50.0)
        return NEEDS_IMPROVEMENT;
    else if (score >= 0.0)
        return AT_RISK;
    else
        return NOT_EVALUATED;
}

const char* statusToString(enum Status s) {
    switch (s) {
        case PASSING: return "Passing";
        case NEEDS_IMPROVEMENT: return "Needs Improvement";
        case AT_RISK: return "At Risk";
        default: return "Not Evaluated";
    }
}

// Function using a pointer to modify a student directly
void updateStudentScore(struct Student *student, float newScore) {
    if (student == NULL) return;
    if (isValidScore(newScore)) {
        student->score = newScore;
        student->status = determineStatus(newScore);
        printf("Score updated successfully!\n");
    } else {
        printf("Invalid score. Score must be between 0 and 100.\n");
    }
}

void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int id;
    char name[NAME_LEN];
    float score;

    printf("Enter student ID: ");
    scanf("%d", &id);
    getchar();

    // Check for duplicate ID
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            printf("Error: Student with ID %d already exists.\n", id);
            return;
        }
    }

    printf("Enter student name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline

    printf("Enter student score (0-100): ");
    scanf("%f", &score);

    if (!isValidScore(score)) {
        printf("Invalid score. Student not added.\n");
        return;
    }

    newStudent.id = id;
    strcpy(newStudent.name, name);
    newStudent.score = score;
    newStudent.status = determineStatus(score);

    students[*count] = newStudent;
    (*count)++;
    printf("Student added successfully! (Total students: %d/%d)\n", *count, MAX_STUDENTS);
}

void displayAllStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("No students in the system.\n");
        return;
    }

    printf("\n%-5s %-20s %-6s %-20s\n", "ID", "Name", "Score", "Status");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-6.2f %-20s\n",
               students[i].id,
               students[i].name,
               students[i].score,
               statusToString(students[i].status));
    }
}
