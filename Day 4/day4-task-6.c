#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

// Enum për statusin
enum Status {
    PASSING,
    NEEDS_IMPROVEMENT,
    AT_RISK,
    NOT_EVALUATED
};

// Struktura e studentit
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
void generateReport(const struct Student students[], int count);
void searchStudent(const struct Student students[], int count);
void updateStudentScore(struct Student *student, float newScore);
void sortAndRankStudents(const struct Student students[], int count); // E RE – renditja
const char* statusToString(enum Status s);
enum Status determineStatus(float score);
int isValidScore(float score);
int getValidInt(int min, int max, const char *prompt);
void clearInputBuffer();
int findStudentIndexById(const struct Student students[], int count, int id);
int compareStudentsByScoreDesc(const void *a, const void *b);

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        choice = getValidInt(1, 7, "Zgjedhja juaj");

        switch (choice) {
            case 1:
                if (studentCount < MAX_STUDENTS)
                    addStudent(students, &studentCount);
                else
                    printf("Nuk mund te shtohen me shume studente. Kapaciteti maksimum %d.\n", MAX_STUDENTS);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                generateReport(students, studentCount);
                break;
            case 4:
                searchStudent(students, studentCount);
                break;
            case 5:
                if (studentCount == 0) {
                    printf("Nuk ka studente ne sistem.\n");
                    break;
                }
                printf("ID e studentit per te perditesuar rezultatin: ");
                int id = getValidInt(1, 9999, "ID");
                int idx = findStudentIndexById(students, studentCount, id);
                if (idx == -1) {
                    printf("Student me ID %d nuk u gjet.\n", id);
                } else {
                    float newScore;
                    printf("Rezultati i ri (0-100): ");
                    while (1) {
                        if (scanf("%f", &newScore) == 1 && isValidScore(newScore)) break;
                        clearInputBuffer();
                        printf("Rezultat i pavlefshem. Provoni perseri: ");
                    }
                    clearInputBuffer();
                    updateStudentScore(&students[idx], newScore);
                }
                break;
            case 6:
                sortAndRankStudents(students, studentCount);   // Opsioni i ri per renditje
                break;
            case 7:
                printf("\nDuke dale nga programi. Mirupafshim!\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

void printMenu() {
    printf("\n========== STUDENT PROGRESS TRACKER ==========\n");
    printf("1. Shto nje student te ri\n");
    printf("2. Shfaq te gjithe studentet\n");
    printf("3. Raport analitik\n");
    printf("4. Kerko student (ID ose emer)\n");
    printf("5. Perditeso rezultatin (permes pointer)\n");
    printf("6. RENDIT DHE RANKO studentet sipas rezultatit\n");
    printf("7. Dil\n");
    printf("===============================================\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidInt(int min, int max, const char *prompt) {
    int value;
    while (1) {
        printf("%s (%d-%d): ", prompt, min, max);
        if (scanf("%d", &value) == 1 && getchar() == '\n' && value >= min && value <= max)
            return value;
        clearInputBuffer();
        printf("Input i pavlefshem. Vendos nje numer midis %d dhe %d.\n", min, max);
    }
}

int isValidScore(float score) {
    return (score >= 0.0 && score <= 100.0);
}

enum Status determineStatus(float score) {
    if (score >= 70.0) return PASSING;
    if (score >= 50.0) return NEEDS_IMPROVEMENT;
    if (score >= 0.0) return AT_RISK;
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

int findStudentIndexById(const struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (students[i].id == id) return i;
    return -1;
}

void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int id;
    char name[NAME_LEN];
    float score;

    printf("ID e studentit: ");
    id = getValidInt(1, 9999, "ID");

    if (findStudentIndexById(students, *count, id) != -1) {
        printf("Gabim: Studenti me ID %d tashme ekziston.\n", id);
        return;
    }

    printf("Emri i studentit: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) strcpy(name, "Anonymous");

    printf("Rezultati (0-100): ");
    while (1) {
        if (scanf("%f", &score) == 1 && isValidScore(score)) break;
        clearInputBuffer();
        printf("Rezultat i pavlefshem. Vendos nje numer midis 0 dhe 100: ");
    }
    clearInputBuffer();

    newStudent.id = id;
    strcpy(newStudent.name, name);
    newStudent.score = score;
    newStudent.status = determineStatus(score);

    students[*count] = newStudent;
    (*count)++;
    printf("Studenti u shtua me sukses! Gjithsej: %d/%d\n", *count, MAX_STUDENTS);
}

void displayAllStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("Nuk ka studente ne sistem.\n");
        return;
    }
    printf("\n%-5s %-20s %-6s %-20s\n", "ID", "Emri", "Rezultati", "Statusi");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-6.2f %-20s\n",
               students[i].id, students[i].name, students[i].score,
               statusToString(students[i].status));
    }
}

void generateReport(const struct Student students[], int count) {
    printf("\n========== RAPORT ANALITIK ==========\n");
    if (count == 0) {
        printf("Nuk ka studente per te gjeneruar raport.\n");
        printf("====================================\n");
        return;
    }
    float sum = 0, highest = students[0].score, lowest = students[0].score;
    int passing = 0, needsImp = 0, atRisk = 0;
    for (int i = 0; i < count; i++) {
        float s = students[i].score;
        sum += s;
        if (s > highest) highest = s;
        if (s < lowest) lowest = s;
        switch (students[i].status) {
            case PASSING: passing++; break;
            case NEEDS_IMPROVEMENT: needsImp++; break;
            case AT_RISK: atRisk++; break;
            default: break;
        }
    }
    float avg = sum / count;
    printf("Numri total i studenteve: %d\n", count);
    printf("Rezultati mesatar: %.2f\n", avg);
    printf("Rezultati me i larte: %.2f\n", highest);
    printf("Rezultati me i ulet: %.2f\n", lowest);
    printf("\nNdarja sipas statusit:\n");
    printf("  - Passing (>=70): %d\n", passing);
    printf("  - Needs Improvement (50-69): %d\n", needsImp);
    printf("  - At Risk (<50): %d\n", atRisk);
    printf("\nKlasifikimi i performances: ");
    if (avg >= 80) printf("★ Shkelqyeshem\n");
    else if (avg >= 60) printf("★ Mire, ka vend per permiresim\n");
    else if (avg >= 40) printf("★ Nevojitet permiresim i ndjeshem\n");
    else printf("★ Gjendje kritike, nderhyrje e menjehershme\n");
    printf("====================================\n");
}

void searchStudent(const struct Student students[], int count) {
    if (count == 0) {
        printf("Nuk ka studente.\n");
        return;
    }
    int type = getValidInt(1, 2, "Kerko sipas (1-ID, 2-Emri)");
    int found = 0;
    if (type == 1) {
        int id = getValidInt(1, 9999, "Jep ID");
        int idx = findStudentIndexById(students, count, id);
        if (idx != -1) {
            printf("\n--- Studenti i gjetur ---\n");
            printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
                   students[idx].id, students[idx].name, students[idx].score,
                   statusToString(students[idx].status));
            found = 1;
        }
    } else {
        char search[NAME_LEN];
        printf("Jep emrin (ose nje pjese te emrit): ");
        fgets(search, NAME_LEN, stdin);
        search[strcspn(search, "\n")] = '\0';
        char lowerSearch[NAME_LEN], lowerName[NAME_LEN];
        for (int i = 0; search[i]; i++) lowerSearch[i] = tolower(search[i]);
        lowerSearch[strlen(search)] = '\0';
        for (int i = 0; i < count; i++) {
            for (int j = 0; students[i].name[j]; j++) lowerName[j] = tolower(students[i].name[j]);
            lowerName[strlen(students[i].name)] = '\0';
            if (strstr(lowerName, lowerSearch)) {
                printf("\n--- Studenti i gjetur ---\n");
                printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
                       students[i].id, students[i].name, students[i].score,
                       statusToString(students[i].status));
                found = 1;
            }
        }
    }
    if (!found) printf("Nuk u gjet asnje student qe perputhet.\n");
}

void updateStudentScore(struct Student *student, float newScore) {
    if (student == NULL) return;
    printf("Rezultati i vjeter: %.2f, Statusi i vjeter: %s\n",
           student->score, statusToString(student->status));
    student->score = newScore;
    student->status = determineStatus(newScore);
    printf("Rezultati i ri: %.2f, Statusi i ri: %s\n",
           student->score, statusToString(student->status));
    printf("Ndryshimi u krye duke perdorur pointer.\n");
}

// Funksioni i krahasimit per qsort (rendit zbrites sipas rezultatit)
int compareStudentsByScoreDesc(const void *a, const void *b) {
    const struct Student *sa = *(const struct Student **)a;
    const struct Student *sb = *(const struct Student **)b;
    if (sa->score > sb->score) return -1;
    if (sa->score < sb->score) return 1;
    return 0;
}

// RENDITJA DHE RANKIMI (KERKESA 6)
void sortAndRankStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("\nNuk ka studente per te renditur.\n");
        return;
    }

    // Krijojme nje varg pointersh pa e ndryshuar vargun origjinal
    const struct Student *ptrs[MAX_STUDENTS];
    for (int i = 0; i < count; i++) {
        ptrs[i] = &students[i];
    }

    // Rendisim pointers-at sipas rezultatit (zbrites)
    qsort(ptrs, count, sizeof(struct Student *), compareStudentsByScoreDesc);

    // Shfaqim renditjen me rang
    printf("\n========== RENDITJA DHE RANKIMI (sipas rezultatit) ==========\n");
    printf("%-5s %-5s %-20s %-6s %-20s\n", "Rangu", "ID", "Emri", "Rezultati", "Statusi");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-5d %-20s %-6.2f %-20s\n",
               i + 1,                     // Rangu (1 = me i miri)
               ptrs[i]->id,
               ptrs[i]->name,
               ptrs[i]->score,
               statusToString(ptrs[i]->status));
    }
    printf("================================================================\n");
}