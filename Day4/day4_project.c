#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 5
#define NAME_LENGTH 50

typedef enum
{
    BEGINNER,
    PROGRESSING,
    COMPLETED
} StudentStatus;

typedef struct
{
    int id;
    char name[NAME_LENGTH];
    float score;
    StudentStatus status;
} StudentRecord;

void showMenu(int recordCount, int maxRecords);
void addStudentRecord(StudentRecord records[], int maxRecords, int *recordCount);
void showStudentRecords(const StudentRecord records[], int recordCount);
void showSingleStudentRecord(const StudentRecord *record, int recordNumber);
void showAnalysisReport(const StudentRecord records[], int recordCount);
void updateStudentRecord(StudentRecord records[], int recordCount);
void updateStudentScore(StudentRecord *record);
void deleteStudentRecord(StudentRecord records[], int *recordCount);
void searchStudentRecords(const StudentRecord records[], int recordCount);
void searchById(const StudentRecord records[], int recordCount);
void searchByName(const StudentRecord records[], int recordCount);
void sortStudentsByScore(StudentRecord records[], int recordCount);
StudentStatus calculateStatus(float score);
void updateRecordCount(int *recordCount);
void reduceRecordCount(int *recordCount);
const char *getStatusText(StudentStatus status);
void clearInputBuffer(void);
int isRecordListFull(int recordCount, int maxRecords);
void showStorageStatus(int recordCount, int maxRecords);
int getIntegerInput(const char *prompt, int *value);
int getFloatInput(const char *prompt, float *value);
int chooseStatusAssignmentMode(void);
int getManualStatus(StudentStatus *status);
const char *getPerformanceMessage(float averageScore);
const char *getRecommendationMessage(float score);
int findStudentIndexById(const StudentRecord records[], int recordCount, int targetId);

int main(void)
{
    StudentRecord records[MAX_STUDENTS];
    int recordCount = 0;
    int menuChoice = 0;
    int isRunning = 1;

    while (isRunning)
    {
        showMenu(recordCount, MAX_STUDENTS);
        printf("Enter your choice: ");
        if (scanf("%d", &menuChoice) != 1)
        {
            printf("\nInvalid input. Please enter a number from the menu.\n");
            clearInputBuffer();
            continue;
        }

        switch (menuChoice)
        {
            case 1:
                addStudentRecord(records, MAX_STUDENTS, &recordCount);
                break;
            case 2:
                showStudentRecords(records, recordCount);
                break;
            case 3:
                showAnalysisReport(records, recordCount);
                break;
            case 4:
                updateStudentRecord(records, recordCount);
                break;
            case 5:
                searchStudentRecords(records, recordCount);
                break;
            case 6:
                sortStudentsByScore(records, recordCount);
                break;
            case 7:
                deleteStudentRecord(records, &recordCount);
                break;
            case 8:
                printf("\nExiting Student Progress Tracker. Goodbye!\n");
                isRunning = 0;
                break;
            default:
                printf("\nInvalid menu choice. Please select a number from 1 to 8.\n");
        }
    }

    return 0;
}

void showMenu(int recordCount, int maxRecords)
{
    printf("\n==============================\n");
    printf("   Student Progress Tracker\n");
    printf("==============================\n");
    showStorageStatus(recordCount, maxRecords);
    printf("1. Add Student Record\n");
    printf("2. Show All Records\n");
    printf("3. Show Analysis Report\n");
    printf("4. Update Student Record\n");
    printf("5. Search Student Record\n");
    printf("6. Sort Students by Score\n");
    printf("7. Delete Student Record\n");
    printf("8. Exit\n");
}

void addStudentRecord(StudentRecord records[], int maxRecords, int *recordCount)
{
    StudentRecord newRecord;
    int statusMode;

    if (isRecordListFull(*recordCount, maxRecords))
    {
        printf("\nThe record list is full. You cannot add more students.\n");
        printf("Storage used: %d/%d\n", *recordCount, maxRecords);
        return;
    }

    if (!getIntegerInput("\nEnter student ID: ", &newRecord.id))
    {
        return;
    }

    printf("Enter student name: ");
    if (fgets(newRecord.name, NAME_LENGTH, stdin) == NULL)
    {
        printf("Could not read the student name.\n");
        return;
    }

    newRecord.name[strcspn(newRecord.name, "\n")] = '\0';

    if (strlen(newRecord.name) == 0)
    {
        printf("Student name cannot be empty.\n");
        return;
    }

    if (!getFloatInput("Enter student score (0-100): ", &newRecord.score))
    {
        return;
    }

    if (newRecord.score < 0 || newRecord.score > 100)
    {
        printf("Score must be between 0 and 100.\n");
        return;
    }

    statusMode = chooseStatusAssignmentMode();

    if (statusMode == 1)
    {
        /* The enum value is assigned automatically from the student's score. */
        newRecord.status = calculateStatus(newRecord.score);
    }
    else if (statusMode == 2)
    {
        if (!getManualStatus(&newRecord.status))
        {
            return;
        }
    }
    else
    {
        printf("Invalid status option. Record was not added.\n");
        return;
    }

    records[*recordCount] = newRecord;
    /* The pointer lets this function update the original count from main. */
    updateRecordCount(recordCount);

    printf("\nStudent record added successfully.\n");
    printf("Records used: %d/%d\n", *recordCount, maxRecords);
    printf("Saved status: %s\n", getStatusText(newRecord.status));

    if (isRecordListFull(*recordCount, maxRecords))
    {
        printf("The student storage is now full.\n");
    }
}

void showStudentRecords(const StudentRecord records[], int recordCount)
{
    int index;

    if (recordCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n===============================================\n");
    printf("               Student Records\n");
    printf("===============================================\n");
    printf("Total Records: %d\n", recordCount);
    printf("===============================================\n");

    for (index = 0; index < recordCount; index++)
    {
        showSingleStudentRecord(&records[index], index + 1);
    }
}

void showSingleStudentRecord(const StudentRecord *record, int recordNumber)
{
    printf("Record %d\n", recordNumber);
    printf("ID: %d\n", record->id);
    printf("Name: %s\n", record->name);
    printf("Score: %.2f\n", record->score);
    printf("Status: %s\n", getStatusText(record->status));
    printf("Recommendation: %s\n", getRecommendationMessage(record->score));
    printf("-----------------------------------------------\n");
}

void showAnalysisReport(const StudentRecord records[], int recordCount)
{
    int index;
    int completedStudents = 0;
    float totalScore = 0.0f;
    float averageScore;
    float highestScore;
    float lowestScore;

    if (recordCount == 0)
    {
        printf("\nNo data available for analysis.\n");
        return;
    }

    highestScore = records[0].score;
    lowestScore = records[0].score;

    for (index = 0; index < recordCount; index++)
    {
        totalScore += records[index].score;

        if (records[index].status == COMPLETED)
        {
            completedStudents++;
        }

        if (records[index].score > highestScore)
        {
            highestScore = records[index].score;
        }
        else if (records[index].score < lowestScore)
        {
            lowestScore = records[index].score;
        }
    }

    averageScore = totalScore / recordCount;

    printf("\n--- ANALYSIS REPORT ---\n");
    printf("Total students: %d\n", recordCount);
    printf("Completed students: %d\n", completedStudents);
    printf("Average score: %.2f\n", averageScore);
    printf("Highest score: %.2f\n", highestScore);
    printf("Lowest score: %.2f\n", lowestScore);
    printf("Message: %s\n", getPerformanceMessage(averageScore));
}

void updateStudentRecord(StudentRecord records[], int recordCount)
{
    int targetId;
    int studentIndex;
    int updateChoice;
    char updatedName[NAME_LENGTH];

    if (recordCount == 0)
    {
        printf("\nNo student records available to update.\n");
        return;
    }

    if (!getIntegerInput("\nEnter the student ID to update: ", &targetId))
    {
        return;
    }

    studentIndex = findStudentIndexById(records, recordCount, targetId);

    if (studentIndex == -1)
    {
        printf("No record found with ID %d.\n", targetId);
        return;
    }

    printf("What do you want to update?\n");
    printf("1. Name\n");
    printf("2. Score\n");
    printf("3. Name and Score\n");

    if (!getIntegerInput("Enter your choice: ", &updateChoice))
    {
        return;
    }

    switch (updateChoice)
    {
        case 1:
        case 3:
            printf("Enter the new name: ");
            if (fgets(updatedName, NAME_LENGTH, stdin) == NULL)
            {
                printf("Could not read the new name.\n");
                return;
            }

            updatedName[strcspn(updatedName, "\n")] = '\0';

            if (strlen(updatedName) == 0)
            {
                printf("Student name cannot be empty.\n");
                return;
            }

            strcpy(records[studentIndex].name, updatedName);

            if (updateChoice == 1)
            {
                break;
            }
        case 2:
            updateStudentScore(&records[studentIndex]);
            break;
        default:
            printf("Invalid update option.\n");
            return;
    }

    printf("\nStudent record updated successfully.\n");
    showSingleStudentRecord(&records[studentIndex], studentIndex + 1);
}

void updateStudentScore(StudentRecord *record)
{
    float newScore;

    if (!getFloatInput("Enter the new score (0-100): ", &newScore))
    {
        return;
    }

    if (newScore < 0 || newScore > 100)
    {
        printf("Score must be between 0 and 100.\n");
        return;
    }

    record->score = newScore;
    record->status = calculateStatus(record->score);
}

void deleteStudentRecord(StudentRecord records[], int *recordCount)
{
    int targetId;
    int studentIndex;
    int index;

    if (*recordCount == 0)
    {
        printf("\nNo student records available to delete.\n");
        return;
    }

    if (!getIntegerInput("\nEnter the student ID to delete: ", &targetId))
    {
        return;
    }

    studentIndex = findStudentIndexById(records, *recordCount, targetId);

    if (studentIndex == -1)
    {
        printf("No record found with ID %d.\n", targetId);
        return;
    }

    for (index = studentIndex; index < *recordCount - 1; index++)
    {
        records[index] = records[index + 1];
    }

    reduceRecordCount(recordCount);
    printf("Student record deleted successfully.\n");
    printf("Records used: %d/%d\n", *recordCount, MAX_STUDENTS);
}

void searchStudentRecords(const StudentRecord records[], int recordCount)
{
    int searchChoice;

    if (recordCount == 0)
    {
        printf("\nNo student records available to search.\n");
        return;
    }

    printf("\nSearch Student Record\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");

    if (!getIntegerInput("Enter your choice: ", &searchChoice))
    {
        return;
    }

    switch (searchChoice)
    {
        case 1:
            searchById(records, recordCount);
            break;
        case 2:
            searchByName(records, recordCount);
            break;
        default:
            printf("Invalid search option.\n");
    }
}

void searchById(const StudentRecord records[], int recordCount)
{
    int targetId;
    int studentIndex;

    if (!getIntegerInput("Enter the student ID to search: ", &targetId))
    {
        return;
    }

    studentIndex = findStudentIndexById(records, recordCount, targetId);

    if (studentIndex == -1)
    {
        printf("No record found.\n");
        return;
    }

    printf("\nMatching record found:\n");
    printf("-----------------------------------------------\n");
    showSingleStudentRecord(&records[studentIndex], studentIndex + 1);
}

void searchByName(const StudentRecord records[], int recordCount)
{
    char searchName[NAME_LENGTH];
    int index;
    int matchFound = 0;

    printf("Enter the student name to search: ");
    if (fgets(searchName, NAME_LENGTH, stdin) == NULL)
    {
        printf("Could not read the search name.\n");
        return;
    }

    searchName[strcspn(searchName, "\n")] = '\0';

    if (strlen(searchName) == 0)
    {
        printf("Search name cannot be empty.\n");
        return;
    }

    printf("\nMatching record(s):\n");
    printf("-----------------------------------------------\n");

    for (index = 0; index < recordCount; index++)
    {
        if (strcmp(records[index].name, searchName) == 0)
        {
            showSingleStudentRecord(&records[index], index + 1);
            matchFound = 1;
        }
    }

    if (!matchFound)
    {
        printf("No record found.\n");
    }
}

void sortStudentsByScore(StudentRecord records[], int recordCount)
{
    int outerIndex;
    int innerIndex;
    StudentRecord temporaryRecord;

    if (recordCount == 0)
    {
        printf("\nNo student records available to sort.\n");
        return;
    }

    for (outerIndex = 0; outerIndex < recordCount - 1; outerIndex++)
    {
        for (innerIndex = 0; innerIndex < recordCount - 1 - outerIndex; innerIndex++)
        {
            if (records[innerIndex].score < records[innerIndex + 1].score)
            {
                temporaryRecord = records[innerIndex];
                records[innerIndex] = records[innerIndex + 1];
                records[innerIndex + 1] = temporaryRecord;
            }
        }
    }

    printf("\nStudents sorted by score from highest to lowest.\n");
    showStudentRecords(records, recordCount);
}

StudentStatus calculateStatus(float score)
{
    if (score < 50)
    {
        return BEGINNER;
    }
    else if (score <= 79)
    {
        return PROGRESSING;
    }
    else
    {
        return COMPLETED;
    }
}

void updateRecordCount(int *recordCount)
{
    (*recordCount)++;
}

void reduceRecordCount(int *recordCount)
{
    if (*recordCount > 0)
    {
        (*recordCount)--;
    }
}

const char *getStatusText(StudentStatus status)
{
    switch (status)
    {
        case BEGINNER:
            return "BEGINNER";
        case PROGRESSING:
            return "PROGRESSING";
        case COMPLETED:
            return "COMPLETED";
        default:
            return "UNKNOWN";
    }
}

void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
    }
}

int isRecordListFull(int recordCount, int maxRecords)
{
    if (recordCount >= maxRecords)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void showStorageStatus(int recordCount, int maxRecords)
{
    printf("Stored Records: %d/%d\n", recordCount, maxRecords);

    if (isRecordListFull(recordCount, maxRecords))
    {
        printf("Status: Storage Full\n");
    }
    else
    {
        printf("Status: Space Available\n");
    }
}

int getIntegerInput(const char *prompt, int *value)
{
    printf("%s", prompt);

    if (scanf("%d", value) != 1)
    {
        printf("Invalid input. Please enter a whole number.\n");
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();
    return 1;
}

int getFloatInput(const char *prompt, float *value)
{
    printf("%s", prompt);

    if (scanf("%f", value) != 1)
    {
        printf("Invalid input. Please enter a numeric value.\n");
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();
    return 1;
}

int chooseStatusAssignmentMode(void)
{
    int mode;

    if (!getIntegerInput("Choose status mode (1 = Automatic by score, 2 = Manual): ", &mode))
    {
        return 0;
    }

    return mode;
}

int getManualStatus(StudentStatus *status)
{
    int statusChoice;

    if (!getIntegerInput("Choose status (1 = BEGINNER, 2 = PROGRESSING, 3 = COMPLETED): ", &statusChoice))
    {
        return 0;
    }

    switch (statusChoice)
    {
        case 1:
            *status = BEGINNER;
            return 1;
        case 2:
            *status = PROGRESSING;
            return 1;
        case 3:
            *status = COMPLETED;
            return 1;
        default:
            printf("Invalid status choice. Record was not added.\n");
            return 0;
    }
}

const char *getPerformanceMessage(float averageScore)
{
    if (averageScore < 50)
    {
        return "Overall performance is low.";
    }
    else if (averageScore <= 79)
    {
        return "Average performance is stable.";
    }
    else
    {
        return "Excellent overall performance.";
    }
}

const char *getRecommendationMessage(float score)
{
    if (score < 50)
    {
        return "Needs improvement";
    }
    else if (score >= 50 && score <= 79)
    {
        return "Keep going";
    }
    else
    {
        return "Excellent";
    }
}

int findStudentIndexById(const StudentRecord records[], int recordCount, int targetId)
{
    int index;

    for (index = 0; index < recordCount; index++)
    {
        if (records[index].id == targetId)
        {
            return index;
        }
    }

    return -1;
}
