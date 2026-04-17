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
            printf("Invalid status input. Please enter a number from 1 to 4.\n");
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
            printf("Invalid status choice. Please choose 1, 2, 3, or 4.\n");
            break;
        }
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
            printf("Invalid menu input. Please enter a number from 1 to 3.\n");
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
            printf("Invalid menu choice. Please choose 1, 2, or 3.\n");
            break;
        }

    } while (choice != 3);

    return 0;
}