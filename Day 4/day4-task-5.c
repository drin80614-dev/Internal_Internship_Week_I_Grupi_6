#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

enum Status {
    PASSING,
    NEEDS_IMPROVEMENT,
    AT_RISK,
    NOT_EVALUATED
};

struct Student {
    int id;
    char name[NAME_LEN];
    float score;
    enum Status status;
};

// Prototipet
void printMenu();
void addStudent(struct Student students[], int *count);
void displayAllStudents(const struct Student students[], int count);
void updateStudentStatus(struct Student students[], int count);
void generateReport(const struct Student students[], int count);
void searchStudent(const struct Student students[], int count);
void updateStudentScore(struct Student *student, float newScore);
void sortAndRankStudents(const struct Student students[], int count);  // E RE: renditje dhe rankim
const char* statusToString(enum Status s);
enum Status determineStatus(float score);
int isValidScore(float score);
int getValidInt(int min, int max, const char *prompt);
void clearInputBuffer();
void updateSingleStudentStatus(struct Student *student);
enum Status getUserSelectedStatus();
void printStudentWithAdvice(const struct Student *s);
int compareStudentsByScoreDesc(const void *a, const void *b); // Funksion krahasimi për qsort

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        choice = getValidInt(1, 8, "Enter your choice"); // Tani 8 opsione

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
                generateReport(students, studentCount);
                break;
            case 5:
                searchStudent(students, studentCount);
                break;
            case 6:
                // Përditësimi i rezultatit duke përdorur pointer
                if (studentCount == 0) {
                    printf("No students in the system. Please add students first.\n");
                    break;
                }
                printf("Enter student ID to update score: ");
                int id = getValidInt(1, 9999, "Student ID");
                int found = -1;
                for (int i = 0; i < studentCount; i++) {
                    if (students[i].id == id) {
                        found = i;
                        break;
                    }
                }
                if (found == -1) {
                    printf("Student with ID %d not found.\n", id);
                } else {
                    float newScore;
                    printf("Enter new score (0-100): ");
                    while (1) {
                        if (scanf("%f", &newScore) == 1 && isValidScore(newScore)) {
                            break;
                        } else {
                            clearInputBuffer();
                            printf("Invalid score. Please enter a number between 0 and 100: ");
                        }
                    }
                    clearInputBuffer();
                    updateStudentScore(&students[found], newScore);
                }
                break;
            case 7:
                sortAndRankStudents(students, studentCount);   // Opsioni i ri për renditje/rankim
                break;
            case 8:
                printf("\nExiting program. Goodbye!\n");
                break;
        }
    } while (choice != 8);

    return 0;
}

void printMenu() {
    printf("\n========== STUDENT PROGRESS TRACKER ==========\n");
    printf("1. Add a new student record\n");
    printf("2. Display all students\n");
    printf("3. Update student status (manual)\n");
    printf("4. Generate analytical report\n");
    printf("5. Search student (by ID or name)\n");
    printf("6. Update student score (using pointer)\n");
    printf("7. Show ranking (sorted by score)\n");
    printf("8. Exit\n");
    printf("===============================================\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt(int min, int max, const char *prompt) {
    int value;
    int result;
    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        result = scanf("%d", &value);
        if (result == 1) {
            if (getchar() == '\n' && value >= min && value <= max) {
                return value;
            } else {
                clearInputBuffer();
                printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            }
        } else {
            clearInputBuffer();
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
        }
    }
}

int isValidScore(float score) {
    return (score >= 0.0 && score <= 100.0);
}

enum Status determineStatus(float score) {
    if (score >= 70.0) return PASSING;
    else if (score >= 50.0) return NEEDS_IMPROVEMENT;
    else if (score >= 0.0) return AT_RISK;
    else return NOT_EVALUATED;
}

const char* statusToString(enum Status s) {
    switch (s) {
        case PASSING: return "Passing";
        case NEEDS_IMPROVEMENT: return "Needs Improvement";
        case AT_RISK: return "At Risk";
        default: return "Not Evaluated";
    }
}

enum Status getUserSelectedStatus() {
    int statusChoice;
    printf("\nSelect new status:\n");
    printf("1. Passing\n");
    printf("2. Needs Improvement\n");
    printf("3. At Risk\n");
    printf("4. Not Evaluated\n");
    statusChoice = getValidInt(1, 4, "Enter status number");
    switch (statusChoice) {
        case 1: return PASSING;
        case 2: return NEEDS_IMPROVEMENT;
        case 3: return AT_RISK;
        default: return NOT_EVALUATED;
    }
}

void updateSingleStudentStatus(struct Student *student) {
    if (student == NULL) return;
    printf("Current status: %s\n", statusToString(student->status));
    enum Status newStatus = getUserSelectedStatus();
    student->status = newStatus;
    printf("Status updated successfully to %s.\n", statusToString(newStatus));
}

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
    updateSingleStudentStatus(&students[found]);
}

void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int id;
    char name[NAME_LEN];
    float score;

    printf("Enter student ID: ");
    id = getValidInt(1, 9999, "Student ID");

    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            printf("Error: Student with ID %d already exists.\n", id);
            return;
        }
    }

    printf("Enter student name: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) strcpy(name, "Unknown");

    printf("Enter student score (0-100): ");
    while (1) {
        if (scanf("%f", &score) == 1 && isValidScore(score)) break;
        else {
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

void generateReport(const struct Student students[], int count) {
    printf("\n========== ANALYTICAL REPORT ==========\n");
    if (count == 0) {
        printf("No students in the system. Cannot generate report.\n");
        printf("=======================================\n");
        return;
    }
    int totalStudents = count;
    float sumScores = 0.0f;
    float highestScore = students[0].score;
    float lowestScore = students[0].score;
    int passingCount = 0, needsImprovementCount = 0, atRiskCount = 0;
    
    for (int i = 0; i < count; i++) {
        float score = students[i].score;
        sumScores += score;
        if (score > highestScore) highestScore = score;
        if (score < lowestScore) lowestScore = score;
        if (students[i].status == PASSING) passingCount++;
        else if (students[i].status == NEEDS_IMPROVEMENT) needsImprovementCount++;
        else if (students[i].status == AT_RISK) atRiskCount++;
    }
    float averageScore = sumScores / count;
    printf("Total students enrolled: %d\n", totalStudents);
    printf("Average score: %.2f\n", averageScore);
    printf("Highest score: %.2f\n", highestScore);
    printf("Lowest score: %.2f\n", lowestScore);
    printf("\nStatus breakdown:\n");
    printf("  - Passing (>=70): %d students\n", passingCount);
    printf("  - Needs Improvement (50-69): %d students\n", needsImprovementCount);
    printf("  - At Risk (<50): %d students\n", atRiskCount);
    printf("\nPerformance classification:\n");
    if (averageScore >= 80.0) printf("  ★ Excellent overall performance!\n");
    else if (averageScore >= 60.0) printf("  ★ Good, but there is room for improvement.\n");
    else if (averageScore >= 40.0) printf("  ★ Needs significant improvement.\n");
    else printf("  ★ Critical situation. Immediate intervention required.\n");
    if (passingCount >= count * 0.7) printf("  ✓ Majority of students are passing.\n");
    else if (passingCount > 0) printf("  ⚠ Only %d out of %d students are passing.\n", passingCount, count);
    else printf("  ✗ No student is passing. Urgent action needed!\n");
    printf("=======================================\n");
}

void printStudentWithAdvice(const struct Student *s) {
    printf("\n--- Found Student ---\n");
    printf("ID: %d\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Score: %.2f\n", s->score);
    printf("Status: %s\n", statusToString(s->status));
    printf("Advice: ");
    if (s->status == PASSING) {
        if (s->score >= 90.0) printf("Excellent! Keep up the great work! Consider mentoring others.\n");
        else if (s->score >= 80.0) printf("Very good. Encourage them to aim for 90+.\n");
        else printf("Good, but can improve with a little more effort. Target weak areas.\n");
    } else if (s->status == NEEDS_IMPROVEMENT) {
        if (s->score >= 60.0) printf("Close to passing. Recommend extra practice and quizzes.\n");
        else printf("Below passing. Needs tutoring and a study plan.\n");
    } else if (s->status == AT_RISK) {
        if (s->score < 30.0) printf("CRITICAL: Very low score. Immediate intervention required. Contact parents and arrange special help.\n");
        else printf("At risk of failing. Suggest mandatory homework support and regular check-ins.\n");
    } else {
        printf("Not evaluated. Please update the student's score/status.\n");
    }
}

void searchStudent(const struct Student students[], int count) {
    if (count == 0) {
        printf("No students in the system. Cannot search.\n");
        return;
    }
    int searchType;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name (partial match, case-insensitive)\n");
    searchType = getValidInt(1, 2, "Choose search type");
    int foundAny = 0;
    if (searchType == 1) {
        int targetId;
        printf("Enter student ID: ");
        targetId = getValidInt(1, 9999, "ID");
        for (int i = 0; i < count; i++) {
            if (students[i].id == targetId) {
                printStudentWithAdvice(&students[i]);
                foundAny = 1;
                break;
            }
        }
        if (!foundAny) printf("No student found with ID %d.\n", targetId);
    } else {
        char searchName[NAME_LEN];
        printf("Enter name (or part of name): ");
        fgets(searchName, NAME_LEN, stdin);
        searchName[strcspn(searchName, "\n")] = '\0';
        char lowerSearch[NAME_LEN], lowerStored[NAME_LEN];
        for (int i = 0; searchName[i]; i++) lowerSearch[i] = tolower(searchName[i]);
        lowerSearch[strlen(searchName)] = '\0';
        for (int i = 0; i < count; i++) {
            for (int j = 0; students[i].name[j]; j++) lowerStored[j] = tolower(students[i].name[j]);
            lowerStored[strlen(students[i].name)] = '\0';
            if (strstr(lowerStored, lowerSearch) != NULL) {
                printStudentWithAdvice(&students[i]);
                foundAny = 1;
            }
        }
        if (!foundAny) printf("No student found with name containing \"%s\".\n", searchName);
    }
}

void updateStudentScore(struct Student *student, float newScore) {
    if (student == NULL) {
        printf("Error: Null pointer received.\n");
        return;
    }
    printf("Old score: %.2f, Old status: %s\n", student->score, statusToString(student->status));
    student->score = newScore;
    student->status = determineStatus(newScore);
    printf("New score: %.2f, New status: %s\n", student->score, statusToString(student->status));
    printf("Score updated successfully using pointer!\n");
}

// Funksion krahasimi për qsort (rendit zbritës sipas rezultatit)
int compareStudentsByScoreDesc(const void *a, const void *b) {
    const struct Student *sa = *(const struct Student **)a;
    const struct Student *sb = *(const struct Student **)b;
    if (sa->score > sb->score) return -1;
    if (sa->score < sb->score) return 1;
    return 0;
}

// Rendit dhe shfaq rangun e studentëve sipas rezultatit (nga më i larti tek më i ulti)
void sortAndRankStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("No students in the system. Cannot rank.\n");
        return;
    }

    // Krijojmë një array treguesish (pointers) për të mos ndryshuar array-n origjinal
    const struct Student *ptrs[MAX_STUDENTS];
    for (int i = 0; i < count; i++) {
        ptrs[i] = &students[i];
    }

    // Rendit treguesit sipas rezultatit (descending) duke përdorur qsort
    qsort(ptrs, count, sizeof(struct Student *), compareStudentsByScoreDesc);

    printf("\n========== STUDENT RANKING (by score) ==========\n");
    printf("%-5s %-5s %-20s %-6s %-20s\n", "Rank", "ID", "Name", "Score", "Status");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        // Në rast barazimi, i njëjti rank (nëse dëshironi trajtim më të sofistikuar, mund të shtohet)
        // Këtu thjesht rreshti i parë ka rank 1, i dyti 2, etj.
        printf("%-5d %-5d %-20s %-6.2f %-20s\n",
               i + 1,
               ptrs[i]->id,
               ptrs[i]->name,
               ptrs[i]->score,
               statusToString(ptrs[i]->status));
    }
    printf("================================================\n");
}