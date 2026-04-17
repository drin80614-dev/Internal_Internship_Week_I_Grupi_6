#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

// Enum for student status - përdoret praktikisht në gjithë programin
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
void updateStudentStatus(struct Student students[], int count);  // Funksion i ri me switch për status
const char* statusToString(enum Status s);
enum Status determineStatus(float score);
int isValidScore(float score);
int getValidInt(int min, int max, const char *prompt);  // Validim i fortë për numra
void clearInputBuffer();

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        choice = getValidInt(1, 4, "Enter your choice"); // Tani 4 opsione

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
                updateStudentStatus(students, studentCount);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

void printMenu() {
    printf("\n===== Student Progress Tracker =====\n");
    printf("1. Add a new student record\n");
    printf("2. Display all students\n");
    printf("3. Update student status (manual)\n");
    printf("4. Exit\n");
    printf("===================================\n");
}

// Pastron buffer-in e input-it
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lexon një numër të plotë brenda intervalit [min, max] dhe ripërsërit nëse gabon
int getValidInt(int min, int max, const char *prompt) {
    int value;
    int result;
    char term;
    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        result = scanf("%d", &value);
        // Kontrollo nëse leximi ishte i suksesshëm dhe nuk ka karaktere të tepërta
        if (result == 1) {
            term = getchar();
            if (term == '\n' && value >= min && value <= max) {
                return value;
            } else {
                // Flak çdo gjë tjetër në buffer
                clearInputBuffer();
                printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            }
        } else {
            // Nëse nuk ishte numër, pastro buffer dhe provo përsëri
            clearInputBuffer();
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
    }
}

int isValidScore(float score) {
    return (score >= 0.0 && score <= 100.0);
}

// Përcakton statusin automatikisht nga rezultati
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

// Kthen enum-in nga inputi i përdoruesit duke përdorur SWITCH
enum Status getUserSelectedStatus() {
    int statusChoice;
    printf("\nSelect new status:\n");
    printf("1. Passing\n");
    printf("2. Needs Improvement\n");
    printf("3. At Risk\n");
    printf("4. Not Evaluated\n");
    
    statusChoice = getValidInt(1, 4, "Enter status number");
    
    switch (statusChoice) {   // Switch-i i dytë në program (për status)
        case 1:
            return PASSING;
        case 2:
            return NEEDS_IMPROVEMENT;
        case 3:
            return AT_RISK;
        case 4:
        default:
            return NOT_EVALUATED;
    }
}

// Përditëson statusin e një studenti ekzistues (përdor pointer për studentin)
void updateSingleStudentStatus(struct Student *student) {
    if (student == NULL) return;
    printf("Current status: %s\n", statusToString(student->status));
    enum Status newStatus = getUserSelectedStatus();
    student->status = newStatus;
    printf("Status updated successfully to %s.\n", statusToString(newStatus));
}

// Gjen studentin me ID dhe përditëson statusin e tij
void updateStudentStatus(struct Student students[], int count) {
    if (count == 0) {
        printf("No students in the system. Please add students first.\n");
        return;
    }
    
    int id;
    printf("Enter student ID to update status: ");
    id = getValidInt(1, 9999, "Student ID");
    
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Student with ID %d not found.\n", id);
        return;
    }
    
    // Thirr funksionin që përdor pointer për të modifikuar studentin
    updateSingleStudentStatus(&students[found]);
}

void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int id;
    char name[NAME_LEN];
    float score;

    printf("Enter student ID: ");
    id = getValidInt(1, 9999, "Student ID");

    // Check for duplicate ID
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            printf("Error: Student with ID %d already exists.\n", id);
            return;
        }
    }

    printf("Enter student name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) {
        strcpy(name, "Unknown");
    }

    printf("Enter student score (0-100): ");
    while (1) {
        if (scanf("%f", &score) == 1 && isValidScore(score)) {
            break;
        } else {
            clearInputBuffer();
            printf("Invalid score. Please enter a number between 0 and 100: ");
        }
    }
    clearInputBuffer();

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
