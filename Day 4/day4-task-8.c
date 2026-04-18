#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STUDENTS 10
#define NAME_LEN 50

// ==================== ENUM DHE STRUCT ====================
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

// ==================== PROTOTIPET ====================
void printMenu();
void printHeader(const char *title);
void clearInputBuffer();
int getValidInt(int min, int max, const char *prompt);
float getValidScore();
int isValidScore(float score);
enum Status determineStatus(float score);
const char* statusToString(enum Status s);
int findStudentIndexById(const struct Student students[], int count, int id);

void addStudent(struct Student students[], int *count);
void displayAllStudents(const struct Student students[], int count);
void updateStudentScore(struct Student *student, float newScore);
void generateReport(const struct Student students[], int count);
void searchStudent(const struct Student students[], int count);
void sortAndRankStudents(const struct Student students[], int count);
void editStudent(struct Student students[], int count);
void deleteStudentById(struct Student students[], int *count);

// ==================== FUNKSIONI KRYESOR ====================
int main() {
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    do {
        printMenu();
        choice = getValidInt(1, 10, "Zgjedhja juaj");

        switch (choice) {
            case 1:
                if (studentCount < MAX_STUDENTS)
                    addStudent(students, &studentCount);
                else
                    printf("\n[!] Nuk mund te shtohen me shume studente. Kapaciteti maksimum %d.\n", MAX_STUDENTS);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                if (studentCount == 0) printf("\n[!] Nuk ka studente ne sistem.\n");
                else {
                    int id = getValidInt(1, 9999, "ID e studentit per te perditesuar rezultatin");
                    int idx = findStudentIndexById(students, studentCount, id);
                    if (idx == -1) printf("\n[!] Student me ID %d nuk u gjet.\n", id);
                    else {
                        float newScore = getValidScore();
                        updateStudentScore(&students[idx], newScore);
                    }
                }
                break;
            case 4:
                generateReport(students, studentCount);
                break;
            case 5:
                searchStudent(students, studentCount);
                break;
            case 6:
                sortAndRankStudents(students, studentCount);
                break;
            case 7:
                editStudent(students, studentCount);
                break;
            case 8:
                deleteStudentById(students, &studentCount);
                break;
            case 9:
                printHeader("PERMBLEDHJE E FUNKSIONALITETEVE");
                printf("1. Shtim studenti\n2. Shfaqje e te gjitheve\n");
                printf("3. Perditesim rezultati (permes pointer)\n4. Raport analitik\n");
                printf("5. Kerkim (ID ose emer)\n6. Renditje/Rankim sipas rezultatit\n");
                printf("7. Ndryshim i te dhenave (emri dhe/ose rezultati)\n8. Fshirje sipas ID\n");
                printf("9. Kjo meny ndihmese\n10. Dalje\n");
                break;
            case 10:
                printf("\n[+] Duke dale nga programi. Mirupafshim!\n");
                break;
        }
    } while (choice != 10);

    return 0;
}

// ==================== FUNKSIONET NDIHMESE ====================
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
        printf("[!] Input i pavlefshem. Vendos nje numer midis %d dhe %d.\n", min, max);
    }
}

float getValidScore() {
    float score;
    while (1) {
        printf("Rezultati i ri (0-100): ");
        if (scanf("%f", &score) == 1 && isValidScore(score)) {
            clearInputBuffer();
            return score;
        }
        clearInputBuffer();
        printf("[!] Rezultat i pavlefshem. Vendos nje numer midis 0 dhe 100.\n");
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

void printHeader(const char *title) {
    printf("\n========== %s ==========\n", title);
}

// ==================== MENUJA ====================
void printMenu() {
    printf("\n========== STUDENT PROGRESS TRACKER ==========\n");
    printf(" 1. Shto nje student te ri\n");
    printf(" 2. Shfaq te gjithe studentet\n");
    printf(" 3. Perditeso rezultatin (permes pointer)\n");
    printf(" 4. Raport analitik\n");
    printf(" 5. Kerko student (ID ose emer)\n");
    printf(" 6. Rendit dhe ranko studentet sipas rezultatit\n");
    printf(" 7. Ndrysho te dhenat e nje studenti\n");
    printf(" 8. Fshije nje student sipas ID\n");
    printf(" 9. Permbledhje e funksionaliteteve\n");
    printf("10. Dil\n");
    printf("===============================================\n");
}

// ==================== KERKESA 1: SHTIM DHE SFAQJE ====================
void addStudent(struct Student students[], int *count) {
    struct Student newStudent;
    int id = getValidInt(1, 9999, "ID e studentit");

    if (findStudentIndexById(students, *count, id) != -1) {
        printf("[!] Gabim: Studenti me ID %d tashme ekziston.\n", id);
        return;
    }

    printf("Emri i studentit: ");
    fgets(newStudent.name, NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    if (strlen(newStudent.name) == 0) strcpy(newStudent.name, "Anonymous");

    newStudent.id = id;
    newStudent.score = getValidScore();
    newStudent.status = determineStatus(newStudent.score);

    students[*count] = newStudent;
    (*count)++;
    printf("[+] Studenti u shtua me sukses! Gjithsej: %d/%d\n", *count, MAX_STUDENTS);
}

void displayAllStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("\n[!] Nuk ka studente ne sistem.\n");
        return;
    }
    printHeader("LISTA E STUDENTEVE");
    printf("%-5s %-20s %-8s %-22s\n", "ID", "Emri", "Rezultati", "Statusi");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-8.2f %-22s\n",
               students[i].id, students[i].name, students[i].score,
               statusToString(students[i].status));
    }
}

// ==================== KERKESA 4: POINTER PER MODIFIKIM ====================
void updateStudentScore(struct Student *student, float newScore) {
    printf("[*] Rezultati i vjeter: %.2f, Statusi: %s\n",
           student->score, statusToString(student->status));
    student->score = newScore;
    student->status = determineStatus(newScore);
    printf("[+] Rezultati i ri: %.2f, Statusi i ri: %s\n",
           student->score, statusToString(student->status));
    printf("[*] Ndryshimi u krye duke perdorur pointer.\n");
}

// ==================== KERKESA 3: RAPORT ANALITIK ====================
void generateReport(const struct Student students[], int count) {
    printHeader("RAPORT ANALITIK");
    if (count == 0) {
        printf("[!] Nuk ka studente per te gjeneruar raport.\n");
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
    printf("Total studente: %d\n", count);
    printf("Mesatarja: %.2f\n", avg);
    printf("Rezultati me i larte: %.2f\n", highest);
    printf("Rezultati me i ulet: %.2f\n", lowest);
    printf("\nNdarja sipas statusit:\n");
    printf("  - Passing (>=70): %d\n", passing);
    printf("  - Needs Improvement (50-69): %d\n", needsImp);
    printf("  - At Risk (<50): %d\n", atRisk);
    printf("\nKlasifikimi: ");
    if (avg >= 80) printf("★ Shkelqyeshem\n");
    else if (avg >= 60) printf("★ Mire, ka vend per permiresim\n");
    else if (avg >= 40) printf("★ Nevojitet permiresim i ndjeshem\n");
    else printf("★ Gjendje kritike, nderhyrje e menjehershme\n");
}

// ==================== KERKESA 5: KERKIMI ====================
void searchStudent(const struct Student students[], int count) {
    if (count == 0) {
        printf("\n[!] Nuk ka studente.\n");
        return;
    }
    int type = getValidInt(1, 2, "Kerko sipas (1-ID, 2-Emri)");
    int found = 0;
    if (type == 1) {
        int id = getValidInt(1, 9999, "Jep ID");
        int idx = findStudentIndexById(students, count, id);
        if (idx != -1) {
            printHeader("STUDENTI I GJETUR");
            printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
                   students[idx].id, students[idx].name, students[idx].score,
                   statusToString(students[idx].status));
            found = 1;
        }
    } else {
        char search[NAME_LEN];
        printf("Jep emrin (ose nje pjese): ");
        fgets(search, NAME_LEN, stdin);
        search[strcspn(search, "\n")] = '\0';
        char lowerSearch[NAME_LEN], lowerName[NAME_LEN];
        for (int i = 0; search[i]; i++) lowerSearch[i] = tolower(search[i]);
        lowerSearch[strlen(search)] = '\0';
        for (int i = 0; i < count; i++) {
            for (int j = 0; students[i].name[j]; j++) lowerName[j] = tolower(students[i].name[j]);
            lowerName[strlen(students[i].name)] = '\0';
            if (strstr(lowerName, lowerSearch)) {
                if (!found) printHeader("STUDENTET E GJETUR");
                printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
                       students[i].id, students[i].name, students[i].score,
                       statusToString(students[i].status));
                found = 1;
            }
        }
    }
    if (!found) printf("\n[!] Nuk u gjet asnje student qe perputhet.\n");
}

// ==================== KERKESA 6: RENDITJA ====================
int compareByScoreDesc(const void *a, const void *b) {
    const struct Student *sa = *(const struct Student **)a;
    const struct Student *sb = *(const struct Student **)b;
    return (sb->score > sa->score) - (sb->score < sa->score);
}

void sortAndRankStudents(const struct Student students[], int count) {
    if (count == 0) {
        printf("\n[!] Nuk ka studente per te renditur.\n");
        return;
    }
    const struct Student *ptrs[MAX_STUDENTS];
    for (int i = 0; i < count; i++) ptrs[i] = &students[i];
    qsort(ptrs, count, sizeof(struct Student *), compareByScoreDesc);

    printHeader("RENDITJA DHE RANKIMI (sipas rezultatit)");
    printf("%-5s %-5s %-20s %-8s %-22s\n", "Rangu", "ID", "Emri", "Rezultati", "Statusi");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-5d %-20s %-8.2f %-22s\n",
               i + 1, ptrs[i]->id, ptrs[i]->name, ptrs[i]->score,
               statusToString(ptrs[i]->status));
    }
}

// ==================== KERKESA 7: NDRYSHIM DHE FSHIRJE ====================
void editStudent(struct Student students[], int count) {
    if (count == 0) {
        printf("\n[!] Nuk ka studente per te ndryshuar.\n");
        return;
    }
    int id = getValidInt(1, 9999, "ID e studentit per te ndryshuar");
    int idx = findStudentIndexById(students, count, id);
    if (idx == -1) {
        printf("[!] Student me ID %d nuk u gjet.\n", id);
        return;
    }
    printf("\n[*] Studenti aktual:\n");
    printf("ID: %d | Emri: %s | Rezultati: %.2f | Statusi: %s\n",
           students[idx].id, students[idx].name, students[idx].score,
           statusToString(students[idx].status));

    int editChoice = getValidInt(1, 3, "Ndrysho (1-Emri, 2-Rezultati, 3-Te dyja)");
    if (editChoice == 1 || editChoice == 3) {
        printf("Emri i ri: ");
        fgets(students[idx].name, NAME_LEN, stdin);
        students[idx].name[strcspn(students[idx].name, "\n")] = '\0';
        if (strlen(students[idx].name) == 0) strcpy(students[idx].name, "Anonymous");
    }
    if (editChoice == 2 || editChoice == 3) {
        float newScore = getValidScore();
        students[idx].score = newScore;
        students[idx].status = determineStatus(newScore);
    }
    printf("[+] Te dhenat e studentit u ndryshuan me sukses.\n");
}

void deleteStudentById(struct Student students[], int *count) {
    if (*count == 0) {
        printf("\n[!] Nuk ka studente per te fshire.\n");
        return;
    }
    int id = getValidInt(1, 9999, "ID e studentit per te fshire");
    int idx = findStudentIndexById(students, *count, id);
    if (idx == -1) {
        printf("[!] Student me ID %d nuk u gjet.\n", id);
        return;
    }
    printf("\n[*] Duke fshire studentin:\n");
    printf("ID: %d | Emri: %s | Rezultati: %.2f\n",
           students[idx].id, students[idx].name, students[idx].score);
    int confirm = getValidInt(1, 2, "Shtyp 1 per konfirmim, 2 per anullim");
    if (confirm != 1) {
        printf("[!] Fshirja u anullua.\n");
        return;
    }
    for (int i = idx; i < *count - 1; i++)
        students[i] = students[i + 1];
    (*count)--;
    printf("[+] Studenti me ID %d u fshi. Gjithsej mbeten: %d studente.\n", id, *count);
}