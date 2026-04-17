#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/student_tracker.h"

#define MENU_INVALID 0
#define SEARCH_INVALID 0

typedef enum {
    SEARCH_BY_ID = 1,
    SEARCH_BY_NAME
} SearchOption;

typedef enum {
    DELETE_BY_ID = 1,
    DELETE_BY_INDEX
} DeleteOption;

static void clearRecord(StudentRecord *record)
{
    record->id = 0;
    record->name[0] = '\0';
    record->progressScore = 0.0f;
    record->status = STATUS_BELOW_TARGET;
}

static void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

static int readInteger(const char *prompt, int *value)
{
    printf("%s", prompt);

    if (scanf("%d", value) != 1) {
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();
    return 1;
}

static int readFloat(const char *prompt, float *value)
{
    printf("%s", prompt);

    if (scanf("%f", value) != 1) {
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();
    return 1;
}

static void readText(const char *prompt, char *buffer, int bufferLength)
{
    printf("%s", prompt);

    if (fgets(buffer, bufferLength, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

static void toLowerText(const char *source, char *destination, int destinationSize)
{
    int index;

    for (index = 0; index < destinationSize - 1 && source[index] != '\0'; index++) {
        destination[index] = (char)tolower((unsigned char)source[index]);
    }

    destination[index] = '\0';
}

static int containsIgnoreCase(const char *text, const char *pattern)
{
    char lowerText[NAME_LENGTH];
    char lowerPattern[NAME_LENGTH];

    toLowerText(text, lowerText, NAME_LENGTH);
    toLowerText(pattern, lowerPattern, NAME_LENGTH);

    return strstr(lowerText, lowerPattern) != NULL;
}

static void printSearchRecordHeader(void)
{
    printf("%-6s %-25s %-12s %-18s\n", "ID", "Emri", "Progresi", "Statusi");
    printf("-----------------------------------------------------------------------------------\n");
}

static void printSectionTitle(const char *title)
{
    printf("\n=========================== %s ===========================\n", title);
}

static void printStudentRecordRow(const StudentRecord *record)
{
    printf("%-6d %-25s %-12.2f %-18s\n",
           record->id,
           record->name,
           record->progressScore,
           getStatusText(record->status));
}

static void printTableFooter(void)
{
    printf("-----------------------------------------------------------------------------------\n");
}

static void showNoRecordsMessage(const char *title, const char *message)
{
    printSectionTitle(title);
    printf("%s\n", message);
}

static void displaySingleRecordDetails(const char *label, const StudentRecord *record)
{
    printf("%s\n", label);
    printSearchRecordHeader();
    printStudentRecordRow(record);
    printTableFooter();
}

static void copyRecords(StudentRecord destination[], const StudentRecord source[], int recordCount)
{
    int index;

    for (index = 0; index < recordCount; index++) {
        destination[index] = source[index];
    }
}

static void printRankedRecordRow(int rank, const StudentRecord *record)
{
    printf("%-6d %-6d %-25s %-12.2f %-18s\n",
           rank,
           record->id,
           record->name,
           record->progressScore,
           getStatusText(record->status));
}

static void printRecommendationMessage(const StudentRecord *record)
{
    if (record->progressScore < 50.0f && record->status == STATUS_BELOW_TARGET) {
        printf("Warning: Progresi eshte i ulet dhe statusi tregon se kerkohet vemendje e menjehershme.\n");
    } else if (record->progressScore < 60.0f && record->status != STATUS_COMPLETED) {
        printf("Alert: Rezultati eshte i dobet dhe regjistrimi nuk eshte perfunduar ende.\n");
    } else if (record->progressScore < 75.0f && record->status == STATUS_ON_TRACK) {
        printf("Recommendation: Nxenesi eshte ne rruge te mire, por duhet monitorim i vazhdueshem.\n");
    } else if (record->progressScore >= 85.0f && record->status == STATUS_COMPLETED) {
        printf("Positive: Performanca eshte e forte dhe regjistrimi eshte perfunduar me sukses.\n");
    } else if (record->progressScore >= 75.0f && record->status == STATUS_ON_TRACK) {
        printf("Recommendation: Progres i mire. Vazhdo me te njejtin ritm monitorimi.\n");
    } else {
        printf("Note: Regjistrimi eshte stabil, por mund te perfitoje nga nje kontroll periodik.\n");
    }
}

static void printRecommendation(const StudentRecord *record)
{
    printf("Interpretim / Rekomandim:\n");
    printRecommendationMessage(record);
}

static SearchOption readSearchChoice(void)
{
    int searchChoice;

    printf("\nZgjidh menyren e kerkimit:\n");
    printf("1. Kerko sipas ID-se\n");
    printf("2. Kerko sipas emrit\n");

    if (!readInteger("Zgjedhja e kerkimit: ", &searchChoice)) {
        printf("Ju lutem vendosni nje numer te vlefshem per kerkimin.\n");
        return SEARCH_INVALID;
    }

    switch (searchChoice) {
        case SEARCH_BY_ID:
            return SEARCH_BY_ID;
        case SEARCH_BY_NAME:
            return SEARCH_BY_NAME;
        default:
            printf("Zgjedhje e pavlefshme. Zgjidh 1 ose 2.\n");
            return SEARCH_INVALID;
    }
}

static int idExists(const StudentRecord records[], int recordCount, int id)
{
    int index;

    for (index = 0; index < recordCount; index++) {
        if (records[index].id == id) {
            return 1;
        }
    }

    return 0;
}

static StudentRecord *findRecordById(StudentRecord records[], int recordCount, int id)
{
    int index;

    for (index = 0; index < recordCount; index++) {
        if (records[index].id == id) {
            return &records[index];
        }
    }

    return NULL;
}

static int findRecordIndexById(const StudentRecord records[], int recordCount, int id)
{
    int index;

    for (index = 0; index < recordCount; index++) {
        if (records[index].id == id) {
            return index;
        }
    }

    return -1;
}

static int isValidProgress(float progress)
{
    return progress >= 0.0f && progress <= 100.0f;
}

static int readValidatedProgress(const char *prompt, float *value)
{
    if (!readFloat(prompt, value)) {
        printf("Progresi duhet te jete numer i vlefshem.\n");
        return 0;
    }

    if (!isValidProgress(*value)) {
        printf("Progresi duhet te jete mes 0 dhe 100.\n");
        return 0;
    }

    return 1;
}

static int readValidatedName(char *buffer, int bufferLength)
{
    readText("Vendos emrin e ri te nxenesit: ", buffer, bufferLength);

    if (strlen(buffer) == 0) {
        printf("Emri nuk mund te jete bosh.\n");
        return 0;
    }

    return 1;
}

static DeleteOption readDeleteChoice(void)
{
    int deleteChoice;

    printf("\nZgjidh menyren e fshirjes:\n");
    printf("1. Fshi sipas ID-se\n");
    printf("2. Fshi sipas indeksit te sakte\n");

    if (!readInteger("Zgjedhja e fshirjes: ", &deleteChoice)) {
        printf("Ju lutem vendosni nje numer te vlefshem per fshirjen.\n");
        return 0;
    }

    switch (deleteChoice) {
        case DELETE_BY_ID:
            return DELETE_BY_ID;
        case DELETE_BY_INDEX:
            return DELETE_BY_INDEX;
        default:
            printf("Zgjedhje e pavlefshme. Zgjidh 1 ose 2.\n");
            return 0;
    }
}

static ProgressStatus chooseStatus(void)
{
    int statusChoice;

    while (1) {
        printf("Zgjidh statusin:\n");
        printf("1. Below Target\n");
        printf("2. On Track\n");
        printf("3. Completed\n");

        if (!readInteger("Statusi: ", &statusChoice)) {
            printf("Statusi duhet te jete numer i vlefshem.\n");
            continue;
        }

        switch (statusChoice) {
            case STATUS_BELOW_TARGET:
                return STATUS_BELOW_TARGET;
            case STATUS_ON_TRACK:
                return STATUS_ON_TRACK;
            case STATUS_COMPLETED:
                return STATUS_COMPLETED;
            default:
                printf("Zgjedhje e pavlefshme per statusin. Zgjidh 1, 2 ose 3.\n");
                break;
        }
    }
}

MenuOption readMenuChoice(void)
{
    int userChoice;

    if (!readInteger("Zgjidh nje opsion: ", &userChoice)) {
        printf("Ju lutem vendosni nje numer te vlefshem per menune.\n");
        return MENU_INVALID;
    }

    switch (userChoice) {
        case MENU_ADD_RECORD:
            return MENU_ADD_RECORD;
        case MENU_SHOW_RECORDS:
            return MENU_SHOW_RECORDS;
        case MENU_SHOW_REPORT:
            return MENU_SHOW_REPORT;
        case MENU_SEARCH_RECORDS:
            return MENU_SEARCH_RECORDS;
        case MENU_UPDATE_RECORD:
            return MENU_UPDATE_RECORD;
        case MENU_SHOW_RANKING:
            return MENU_SHOW_RANKING;
        case MENU_EDIT_RECORD:
            return MENU_EDIT_RECORD;
        case MENU_DELETE_RECORD:
            return MENU_DELETE_RECORD;
        case MENU_EXIT:
            return MENU_EXIT;
        default:
            printf("Opsion i pavlefshem. Zgjidh nje numer nga 1 deri ne 9.\n");
            return MENU_INVALID;
    }
}

void initializeRecords(StudentRecord records[], int size)
{
    int index;

    for (index = 0; index < size; index++) {
        clearRecord(&records[index]);
    }
}

void showMenu(int recordCount, int maxStudents)
{
    printf("\n===== Student Progress Tracker =====\n");
    printf("Regjistrime aktive: %d / %d\n", recordCount, maxStudents);
    printf("--------------------------------------------------\n");
    printf("1. Shto regjistrim te ri\n");
    printf("2. Shfaq te gjithe regjistrimet\n");
    printf("3. Shfaq raportin analitik\n");
    printf("4. Kerko regjistrime\n");
    printf("5. Perditeso nje regjistrim ekzistues\n");
    printf("6. Shfaq renditjen sipas progresit\n");
    printf("7. Edito nje regjistrim ekzistues\n");
    printf("8. Fshi nje regjistrim\n");
    printf("9. Dil nga programi\n");
    printf("--------------------------------------------------\n");
}

void addStudentRecord(StudentRecord records[], int size, int *recordCount)
{
    StudentRecord *currentRecord;
    ProgressStatus selectedStatus;
    int newId;

    if (*recordCount >= size) {
        printf("Kufiri maksimal u arrit (%d regjistrime). Nuk lejohen shtime te reja.\n", size);
        return;
    }

    currentRecord = &records[*recordCount];

    if (!readInteger("Vendos ID: ", &newId) || newId <= 0) {
        printf("ID duhet te jete numer pozitiv.\n");
        return;
    }

    if (idExists(records, *recordCount, newId)) {
        printf("Ekziston tashme nje regjistrim me kete ID.\n");
        return;
    }

    currentRecord->id = newId;

    readText("Vendos emrin e nxenesit: ", currentRecord->name, NAME_LENGTH);
    if (strlen(currentRecord->name) == 0) {
        printf("Emri nuk mund te jete bosh.\n");
        return;
    }

    if (!readValidatedProgress("Vendos progresin/rezultatin: ", &currentRecord->progressScore)) {
        return;
    }

    selectedStatus = chooseStatus();
    currentRecord->status = selectedStatus;
    (*recordCount)++;

    printf("Regjistrimi u shtua me sukses. Tani jane ruajtur %d nga %d regjistrime.\n",
           *recordCount,
           size);
}

void displayStudentRecords(const StudentRecord records[], int recordCount)
{
    int index;

    if (recordCount == 0) {
        printf("Nuk ka regjistrime per te shfaqur.\n");
        return;
    }

    printSectionTitle("Lista e Regjistrimeve");
    printSearchRecordHeader();
    for (index = 0; index < recordCount; index++) {
        printStudentRecordRow(&records[index]);
    }
    printTableFooter();
    printf("Totali i regjistrimeve: %d\n", recordCount);
}

void generateAnalyticalReport(const StudentRecord records[], int recordCount)
{
    int index;
    int completedCount = 0;
    float totalProgress = 0.0f;
    float averageProgress;
    float highestProgress;
    float lowestProgress;

    if (recordCount == 0) {
        showNoRecordsMessage("Raporti Analitik", "Nuk ka regjistrime te ruajtura ende.");
        printf("Shto te pakten nje regjistrim per te gjeneruar nje raport te dobishem.\n");
        return;
    }

    highestProgress = records[0].progressScore;
    lowestProgress = records[0].progressScore;

    for (index = 0; index < recordCount; index++) {
        totalProgress += records[index].progressScore;

        if (records[index].status == STATUS_COMPLETED) {
            completedCount++;
        }

        if (records[index].progressScore > highestProgress) {
            highestProgress = records[index].progressScore;
        } else if (records[index].progressScore < lowestProgress) {
            lowestProgress = records[index].progressScore;
        }
    }

    averageProgress = totalProgress / recordCount;

    printSectionTitle("Raporti Analitik");
    printf("Totali i regjistrimeve : %d\n", recordCount);
    printf("Mesatarja e progresit  : %.2f\n", averageProgress);
    printf("Progresi me i larte    : %.2f\n", highestProgress);
    printf("Progresi me i ulet     : %.2f\n", lowestProgress);
    printf("Regjistrime Completed  : %d\n", completedCount);
    printf("-----------------------------------------------------------------------\n");

    if (recordCount < 3) {
        printf("Interpretim: Ka pak te dhena, ndaj raporti eshte ende fillestar.\n");
    } else {
        printf("Interpretim: Ka mjaftueshem te dhena per nje permbledhje te dobishme.\n");
    }

    if (averageProgress < 50.0f) {
        printf("Mesatarja: Progresi i pergjithshem eshte i ulet.\n");
    } else if (averageProgress < 75.0f) {
        printf("Mesatarja: Progresi i pergjithshem eshte ne nivel mesatar.\n");
    } else {
        printf("Mesatarja: Progresi i pergjithshem eshte i larte.\n");
    }

    if (completedCount == 0) {
        printf("Completed: Nuk ka ende regjistrime te perfunduara.\n");
    } else if (completedCount < recordCount / 2.0f) {
        printf("Completed: Ka permiresim per t'u bere ne perfundimin e regjistrimeve.\n");
    } else {
        printf("Completed: Numri i regjistrimeve te perfunduara eshte i kenaqshem.\n");
    }
}

void searchStudentRecords(const StudentRecord records[], int recordCount)
{
    SearchOption searchOption;
    int index;
    int searchId;
    int matchesFound = 0;
    char searchName[NAME_LENGTH];

    if (recordCount == 0) {
        showNoRecordsMessage("Rezultati i Kerkimit",
                             "Nuk ka regjistrime te ruajtura per t'u kerkuar.");
        return;
    }

    searchOption = readSearchChoice();
    if (searchOption == SEARCH_INVALID) {
        return;
    }

    printSectionTitle("Rezultati i Kerkimit");

    switch (searchOption) {
        case SEARCH_BY_ID:
            if (!readInteger("Vendos ID-ne qe do te kerkosh: ", &searchId) || searchId <= 0) {
                printf("ID e kerkimit duhet te jete numer pozitiv.\n");
                return;
            }

            for (index = 0; index < recordCount; index++) {
                if (records[index].id == searchId) {
                    displaySingleRecordDetails("Te dhenat e gjetura:", &records[index]);
                    printRecommendation(&records[index]);
                    matchesFound = 1;
                    break;
                }
            }
            break;

        case SEARCH_BY_NAME:
            readText("Vendos emrin ose nje pjese te emrit: ", searchName, NAME_LENGTH);
            if (strlen(searchName) == 0) {
                printf("Emri i kerkimit nuk mund te jete bosh.\n");
                return;
            }

            printf("Te dhenat e gjetura:\n");
            printSearchRecordHeader();

            for (index = 0; index < recordCount; index++) {
                if (containsIgnoreCase(records[index].name, searchName)) {
                    printStudentRecordRow(&records[index]);
                    matchesFound++;
                }
            }

            if (matchesFound > 0) {
                printTableFooter();
                printf("Totali i perputhjeve: %d\n", matchesFound);
                printf("\nInterpretim / Rekomandim:\n");
                for (index = 0; index < recordCount; index++) {
                    if (containsIgnoreCase(records[index].name, searchName)) {
                        printf("Per %s (ID %d): ", records[index].name, records[index].id);
                        printRecommendationMessage(&records[index]);
                    }
                }
            }
            break;

        default:
            printf("Ndodhi nje gabim ne zgjedhjen e kerkimit.\n");
            return;
    }

    if (matchesFound == 0) {
        printf("Nuk u gjet asnje regjistrim qe perputhet me kerkimin.\n");
    }
}

void updateStudentRecord(StudentRecord records[], int recordCount)
{
    int studentId;
    float newProgress;
    ProgressStatus newStatus;
    StudentRecord *recordToUpdate;

    if (recordCount == 0) {
        showNoRecordsMessage("Perditesimi i Regjistrimit",
                             "Nuk ka regjistrime te ruajtura per t'u perditesuar.");
        return;
    }

    printSectionTitle("Perditesimi i Regjistrimit");

    if (!readInteger("Vendos ID-ne e regjistrimit qe do te perditesosh: ", &studentId) ||
        studentId <= 0) {
        printf("ID duhet te jete numer pozitiv.\n");
        return;
    }

    recordToUpdate = findRecordById(records, recordCount, studentId);
    if (recordToUpdate == NULL) {
        printf("Nuk u gjet regjistrim me ID %d.\n", studentId);
        return;
    }

    printf("Regjistrimi u gjet ne adrese: %p\n", (void *)recordToUpdate);
    displaySingleRecordDetails("Vlera para perditesimit:", recordToUpdate);

    if (!readValidatedProgress("Vendos progresin/rezultatin e ri: ", &newProgress)) {
        return;
    }

    newStatus = chooseStatus();

    recordToUpdate->progressScore = newProgress;
    recordToUpdate->status = newStatus;

    displaySingleRecordDetails("Vlera pas perditesimit me pointer:", recordToUpdate);
    printf("Perditesimi u ruajt ne te dhenat origjinale.\n");
}

void editStudentRecord(StudentRecord records[], int recordCount)
{
    int studentId;
    char newName[NAME_LENGTH];
    float newProgress;
    ProgressStatus newStatus;
    StudentRecord *recordToEdit;

    if (recordCount == 0) {
        showNoRecordsMessage("Editimi i Regjistrimit",
                             "Nuk ka regjistrime te ruajtura per t'u edituar.");
        return;
    }

    printSectionTitle("Editimi i Regjistrimit");

    if (!readInteger("Vendos ID-ne e regjistrimit qe do te editosh: ", &studentId) ||
        studentId <= 0) {
        printf("ID duhet te jete numer pozitiv.\n");
        return;
    }

    recordToEdit = findRecordById(records, recordCount, studentId);
    if (recordToEdit == NULL) {
        printf("Nuk u gjet regjistrim me ID %d.\n", studentId);
        return;
    }

    displaySingleRecordDetails("Vlera aktuale e regjistrimit:", recordToEdit);

    if (!readValidatedName(newName, NAME_LENGTH)) {
        return;
    }

    if (!readValidatedProgress("Vendos progresin/rezultatin e ri: ", &newProgress)) {
        return;
    }

    newStatus = chooseStatus();

    strcpy(recordToEdit->name, newName);
    recordToEdit->progressScore = newProgress;
    recordToEdit->status = newStatus;

    printf("Regjistrimi u editua me sukses.\n");
    displaySingleRecordDetails("Vlera pas editimit:", recordToEdit);
}

void deleteStudentRecord(StudentRecord records[], int *recordCount)
{
    DeleteOption deleteOption;
    int targetId;
    int targetIndex;
    int index;

    if (*recordCount == 0) {
        showNoRecordsMessage("Fshirja e Regjistrimit",
                             "Nuk ka regjistrime te ruajtura per t'u fshire.");
        return;
    }

    printSectionTitle("Fshirja e Regjistrimit");
    deleteOption = readDeleteChoice();
    if (deleteOption == 0) {
        return;
    }

    switch (deleteOption) {
        case DELETE_BY_ID:
            if (!readInteger("Vendos ID-ne e regjistrimit qe do te fshish: ", &targetId) ||
                targetId <= 0) {
                printf("ID duhet te jete numer pozitiv.\n");
                return;
            }

            targetIndex = findRecordIndexById(records, *recordCount, targetId);
            if (targetIndex == -1) {
                printf("Nuk u gjet regjistrim me ID %d.\n", targetId);
                return;
            }
            break;

        case DELETE_BY_INDEX:
            printf("Indekset e vlefshme jane nga 0 deri ne %d.\n", *recordCount - 1);
            if (!readInteger("Vendos indeksin e sakte qe do te fshish: ", &targetIndex)) {
                printf("Indeksi duhet te jete numer i vlefshem.\n");
                return;
            }

            if (targetIndex < 0 || targetIndex >= *recordCount) {
                printf("Indeksi eshte jashte kufijve te vlefshem.\n");
                return;
            }
            break;

        default:
            printf("Ndodhi nje gabim ne fshirje.\n");
            return;
    }

    displaySingleRecordDetails("Regjistrimi qe do te fshihet:", &records[targetIndex]);

    for (index = targetIndex; index < *recordCount - 1; index++) {
        records[index] = records[index + 1];
    }

    (*recordCount)--;
    clearRecord(&records[*recordCount]);

    printf("Regjistrimi u fshi me sukses. Tani jane ruajtur %d regjistrime.\n", *recordCount);
}

void showProgressRanking(const StudentRecord records[], int recordCount)
{
    StudentRecord sortedRecords[MAX_STUDENTS];
    StudentRecord tempRecord;
    int index;
    int innerIndex;

    if (recordCount == 0) {
        showNoRecordsMessage("Renditja Sipas Progresit",
                             "Nuk ka regjistrime te ruajtura per te ndertuar renditjen.");
        return;
    }

    copyRecords(sortedRecords, records, recordCount);

    for (index = 0; index < recordCount - 1; index++) {
        for (innerIndex = 0; innerIndex < recordCount - index - 1; innerIndex++) {
            if (sortedRecords[innerIndex].progressScore <
                sortedRecords[innerIndex + 1].progressScore) {
                tempRecord = sortedRecords[innerIndex];
                sortedRecords[innerIndex] = sortedRecords[innerIndex + 1];
                sortedRecords[innerIndex + 1] = tempRecord;
            }
        }
    }

    printSectionTitle("Renditja Sipas Progresit");
    printf("%-6s %-6s %-25s %-12s %-18s\n",
           "Rank",
           "ID",
           "Emri",
           "Progresi",
           "Statusi");
    printf("-----------------------------------------------------------------------------------\n");

    for (index = 0; index < recordCount; index++) {
        printRankedRecordRow(index + 1, &sortedRecords[index]);
    }

    printTableFooter();
    printf("Renditja u krijua nga vlerat reale te progresit pa ndryshuar rendin origjinal.\n");
}

const char *getStatusText(ProgressStatus status)
{
    switch (status) {
        case STATUS_BELOW_TARGET:
            return "Below Target";
        case STATUS_ON_TRACK:
            return "On Track";
        case STATUS_COMPLETED:
            return "Completed";
        default:
            return "Unknown";
    }
}
