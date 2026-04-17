#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 5

enum Status
{
    FAIL,
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

static void setStatus(int progress, enum Status* status)
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

static void addRecord(struct Student students[], int* count)
{
    struct Student newStudent = { 0 };

    if (*count >= MAX_RECORDS)
    {
        printf("\nMaximum number of records reached. You cannot add more students.\n");
        return;
    }

    if (!readInt("\nEnter student ID: ", &newStudent.id))
    {
        printf("Invalid ID input.\n");
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
        printf("Invalid progress. Please enter a value between 0 and 100.\n");
        return;
    }

    setStatus(newStudent.progress, &newStudent.status);

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
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Progress: %d\n", students[i].progress);
        printf("Status: ");
        printStatus(students[i].status);
        printf("\n");
    }

    printf("\nTotal records: %d / %d\n", count, MAX_RECORDS);
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
        printf("3. Exit\n");

        if (!readInt("Choose an option: ", &choice))
        {
            printf("Invalid menu choice.\n");
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
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

    } while (choice != 3);

    return 0;
}