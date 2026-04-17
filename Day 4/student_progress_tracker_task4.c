#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 5

enum Status
{
    FAIL = 1,
    AVERAGE,
    GOOD,
    EXCELLENT
};

struct Student
{
    int id;
    char name[50];
    int progress;
    enum Status status;
};

static void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

static int readInt(const char* message, int* value)
{
    printf("%s", message);

    if (scanf_s("%d", value) != 1)
    {
        clearInputBuffer();
        return 0;
    }

    clearInputBuffer();
    return 1;
}

static int readString(const char* message, char text[], int size)
{
    size_t length;

    printf("%s", message);

    if (fgets(text, size, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(text);

    if (length > 0 && text[length - 1] == '\n')
    {
        text[length - 1] = '\0';
    }
    else
    {
        clearInputBuffer();
    }

    if (strlen(text) == 0)
    {
        return 0;
    }

    return 1;
}

static void setStatusFromProgress(int progress, enum Status* status)
{
    if (progress < 50)
    {
        *status = FAIL;
    }
    else if (progress < 70)
    {
        *status = AVERAGE;
    }
    else if (progress < 90)
    {
        *status = GOOD;
    }
    else
    {
        *status = EXCELLENT;
    }
}

static void printStatus(enum Status status)
{
    switch (status)
    {
    case FAIL:
        printf("Fail");
        break;
    case AVERAGE:
        printf("Average");
        break;
    case GOOD:
        printf("Good");
        break;
    case EXCELLENT:
        printf("Excellent");
        break;
    default:
        printf("Unknown");
        break;
    }
}

static int chooseStatus(enum Status* status)
{
    int choice = 0;

    while (1)
    {
        printf("\nChoose student status:\n");
        printf("1. Fail\n");
        printf("2. Average\n");
        printf("3. Good\n");
        printf("4. Excellent\n");

        if (!readInt("Enter status choice: ", &choice))
        {
            printf("Invalid status input.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            *status = FAIL;
            return 1;
        case 2:
            *status = AVERAGE;
            return 1;
        case 3:
            *status = GOOD;
            return 1;
        case 4:
            *status = EXCELLENT;
            return 1;
        default:
            printf("Invalid status choice.\n");
            break;
        }
    }
}

static void showSingleRecord(const struct Student* student)
{
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Progress: %d\n", student->progress);
    printf("Status: ");
    printStatus(student->status);
    printf("\n");
}

static int findStudentIndexById(const struct Student students[], int count, int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

static void addRecord(struct Student students[], int* count)
{
    struct Student newStudent = { 0 };

    if (*count >= MAX_RECORDS)
    {
        printf("\nMaximum number of records reached.\n");
        return;
    }

    if (!readInt("\nEnter student ID: ", &newStudent.id))
    {
        printf("Invalid ID input.\n");
        return;
    }

    if (findStudentIndexById(students, *count, newStudent.id) != -1)
    {
        printf("A student with this ID already exists.\n");
        return;
    }

    if (!readString("Enter student name: ", newStudent.name, sizeof(newStudent.name)))
    {
        printf("Invalid name input.\n");
        return;
    }

    if (!readInt("Enter student progress (0-100): ", &newStudent.progress))
    {
        printf("Invalid progress input.\n");
        return;
    }

    if (newStudent.progress < 0 || newStudent.progress > 100)
    {
        printf("Progress must be between 0 and 100.\n");
        return;
    }

    if (!chooseStatus(&newStudent.status))
    {
        return;
    }

    students[*count] = newStudent;
    (*count)++;

    printf("Record added successfully.\n");
}

static void showAllRecords(const struct Student students[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    printf("\n----- Student Progress Records -----\n");

    for (i = 0; i < count; i++)
    {
        printf("\nRecord %d\n", i + 1);
        showSingleRecord(&students[i]);
    }
}

static void showReport(const struct Student students[], int count)
{
    int i;
    int totalProgress = 0;
    int highestProgress;
    int lowestProgress;
    double averageProgress;

    if (count == 0)
    {
        printf("\nNo records available. Report cannot be generated.\n");
        return;
    }

    highestProgress = students[0].progress;
    lowestProgress = students[0].progress;

    for (i = 0; i < count; i++)
    {
        totalProgress += students[i].progress;

        if (students[i].progress > highestProgress)
        {
            highestProgress = students[i].progress;
        }

        if (students[i].progress < lowestProgress)
        {
            lowestProgress = students[i].progress;
        }
    }

    averageProgress = (double)totalProgress / count;

    printf("\n========== Student Report ==========\n");
    printf("Total records: %d\n", count);
    printf("Average progress: %.2f\n", averageProgress);
    printf("Highest progress: %d\n", highestProgress);
    printf("Lowest progress: %d\n", lowestProgress);
}

static void updateStudentProgress(struct Student* student, int newProgress)
{
    student->progress = newProgress;
    setStatusFromProgress(student->progress, &student->status);
}

static void updateProgressById(struct Student students[], int count)
{
    int id;
    int index;
    int newProgress;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    if (!readInt("\nEnter student ID to update progress: ", &id))
    {
        printf("Invalid ID input.\n");
        return;
    }

    index = findStudentIndexById(students, count, id);

    if (index == -1)
    {
        printf("Student not found.\n");
        return;
    }

    if (!readInt("Enter new progress (0-100): ", &newProgress))
    {
        printf("Invalid progress input.\n");
        return;
    }

    if (newProgress < 0 || newProgress > 100)
    {
        printf("Progress must be between 0 and 100.\n");
        return;
    }

    updateStudentProgress(&students[index], newProgress);

    printf("Progress updated successfully.\n");
}

static void printSearchMessage(const struct Student* student)
{
    printf("Evaluation: ");

    if (student->progress < 40 && student->status == FAIL)
    {
        printf("Urgent warning. The student is at serious risk and needs immediate support.\n");
    }
    else if (student->progress < 50 || student->status == FAIL)
    {
        printf("Warning. The student should improve performance soon.\n");
    }
    else if (student->progress >= 50 && student->progress < 70 && student->status == AVERAGE)
    {
        printf("Recommendation. The student is passing but still needs more practice.\n");
    }
    else if (student->progress >= 70 && student->status == GOOD)
    {
        printf("Positive result. The student is doing well.\n");
    }
    else if (student->progress >= 90 && student->status == EXCELLENT)
    {
        printf("Excellent result. Keep up the strong performance.\n");
    }
    else
    {
        printf("Mixed result. Review the student record carefully.\n");
    }
}

static void searchById(const struct Student students[], int count)
{
    int id;
    int index;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    if (!readInt("\nEnter ID to search: ", &id))
    {
        printf("Invalid ID input.\n");
        return;
    }

    index = findStudentIndexById(students, count, id);

    if (index == -1)
    {
        printf("No student found with that ID.\n");
        return;
    }

    printf("\nSearch result:\n");
    showSingleRecord(&students[index]);
    printSearchMessage(&students[index]);
}

static void searchByName(const struct Student students[], int count)
{
    char name[50];
    int i;
    int found = 0;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    if (!readString("\nEnter name to search: ", name, sizeof(name)))
    {
        printf("Invalid name input.\n");
        return;
    }

    printf("\nSearch results:\n");

    for (i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            printf("\nMatched record:\n");
            showSingleRecord(&students[i]);
            printSearchMessage(&students[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No student found with that name.\n");
    }
}

static void searchRecord(const struct Student students[], int count)
{
    int choice;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nSearch menu:\n");
    printf("1. Search by ID\n");
    printf("2. Search by name\n");

    if (!readInt("Choose search option: ", &choice))
    {
        printf("Invalid search input.\n");
        return;
    }

    switch (choice)
    {
    case 1:
        searchById(students, count);
        break;
    case 2:
        searchByName(students, count);
        break;
    default:
        printf("Invalid search choice.\n");
        break;
    }
}

int main(void)
{
    struct Student students[MAX_RECORDS] = { 0 };
    int count = 0;
    int choice = 0;

    do
    {
        printf("\n===== Student Progress Tracker =====\n");
        printf("1. Add record\n");
        printf("2. Show all records\n");
        printf("3. Show report\n");
        printf("4. Update progress by ID\n");
        printf("5. Search record\n");
        printf("6. Exit\n");

        if (!readInt("Choose an option: ", &choice))
        {
            printf("Invalid menu input.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            addRecord(students, &count);
            break;
        case 2:
            showAllRecords(students, count);
            break;
        case 3:
            showReport(students, count);
            break;
        case 4:
            updateProgressById(students, count);
            break;
        case 5:
            searchRecord(students, count);
            break;
        case 6:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid menu choice.\n");
            break;
        }

    } while (choice != 6);

    return 0;
}