#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

enum Status { PASSING, NEEDS_IMPROVEMENT, AT_RISK, NOT_EVALUATED };

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
void editStudent(struct Student students[], int count);        // Ndryshim i 2 fushave
void deleteStudentById(struct Student students[], int *count); // Fshirje
const char* statusToString(enum Status s);
enum Status determineStatus(float score);
int isValidScore(float score);
int getValidInt(int min, int max, const char *prompt);
void clearInputBuffer();
int findStudentIndexById(const struct Student students[], int count, int id);

int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        choice = getValidInt(1, 5, "Zgjedhja juaj");

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
                editStudent(students, studentCount);
                break;
            case 4:
                deleteStudentById(students, &studentCount);
                break;
            case 5:
                printf("\nDuke dale nga programi. Mirupafshim!\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

void printMenu() {
    printf("\n========== STUDENT PROGRESS TRACKER ==========\n");
    printf("1. Shto nje student te ri\n");
    printf("2. Shfaq te gjithe studentet\n");
    printf("3. Ndrysho te dhenat e nje studenti (emri dhe/ose rezultati)\n");
    printf("4. Fshije nje student sipas ID\n");
    printf("5. Dil\n");
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
    int id = getValidInt(1, 9999, "ID e studentit");
    if (findStudentIndexById(students, *count, id) != -1) {
        printf("Gabim: Studenti me ID %d tashme ekziston.\n", id);
        return;
    }

    char name[NAME_LEN];
    printf("Emri i studentit: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';
    if (strlen(name) == 0) strcpy(name, "Anonymous");

    float score;
    printf("Rezultati (0-100): ");
    while (1) {
        if (scanf("%f", &score) == 1 && isValidScore(score)) break;
        clearInputBuffer();
        printf("Rezultat i pavlefshem. Provoni perseri: ");
    }
    clearInputBuffer();

    struct Student newStudent;
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

// NDRYSHIMI I TE PAKTEN 2 FUSHAVE (emri dhe rezultati)
void editStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("Nuk ka studente per te ndryshuar.\n");
        return;
    }

    int id = getValidInt(1, 9999, "ID e studentit qe doni te ndryshoni");
    int idx = findStudentIndexById(students, count, id);
    if (idx == -1) {
        printf("Student me ID %d nuk u gjet.\n", id);
        return;
    }

    printf("\nStudent i zgjedhur:\n");
    printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
           students[idx].id, students[idx].name, students[idx].score,
           statusToString(students[idx].status));

    int editChoice = getValidInt(1, 3, "Ndrysho (1-Emri, 2-Rezultati, 3-Te dyja)");

    if (editChoice == 1 || editChoice == 3) {
        char newName[NAME_LEN];
        printf("Emri i ri: ");
        fgets(newName, NAME_LEN, stdin);
        newName[strcspn(newName, "\n")] = '\0';
        if (strlen(newName) > 0) {
            strcpy(students[idx].name, newName);
            printf("Emri u ndryshua.\n");
        }
    }

    if (editChoice == 2 || editChoice == 3) {
        float newScore;
        printf("Rezultati i ri (0-100): ");
        while (1) {
            if (scanf("%f", &newScore) == 1 && isValidScore(newScore)) break;
            clearInputBuffer();
            printf("Rezultat i pavlefshem. Provoni perseri: ");
        }
        clearInputBuffer();
        students[idx].score = newScore;
        students[idx].status = determineStatus(newScore);
        printf("Rezultati dhe statusi u perditesuan.\n");
    }

    printf("Te dhenat e studentit u ndryshuan me sukses.\n");
}

// FSHIRJA E NJE REGJISTRIMI SIPAS ID (me zhvendosje te elementeve)
void deleteStudentById(struct Student students[], int *count) {
    if (*count == 0) {
        printf("Nuk ka studente per te fshire.\n");
        return;
    }

    int id = getValidInt(1, 9999, "ID e studentit qe doni te fshini");
    int idx = findStudentIndexById(students, *count, id);
    if (idx == -1) {
        printf("Student me ID %d nuk u gjet.\n", id);
        return;
    }

    // Konfirmimi para fshirjes
    printf("\nJeni duke fshire studentin:\n");
    printf("ID: %d | Emri: %s | Rezultati: %.2f\n",
           students[idx].id, students[idx].name, students[idx].score);
    int confirm = getValidInt(1, 2, "Shtyp 1 per te konfirmuar fshirjen, 2 per anullim");
    if (confirm != 1) {
        printf("Fshirja u anullua.\n");
        return;
    }

    // Zhvendos te gjithe elementet nga idx+1 nje pozite majtas
    for (int i = idx; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    (*count)--;

    printf("Studenti me ID %d u fshi me sukses. Gjithsej mbeten: %d studente.\n", id, *count);
}