#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int size;
    int choice;

    printf("Choose the pattern size (1-12): ");
    if (scanf("%d", &size) != 1)
    {
        printf("Invalid input. Please enter a whole number.\n");
        return 1;
    }

    if (size < 1 || size > 12)
    {
        printf("Invalid input. Size must be between 1 and 12.\n");
        return 1;
    }

    printf("\nChoose the pattern type:\n");
    printf("1. Star pattern\n");
    printf("2. Number pattern\n");
    printf("Enter your choice (1 or 2): ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input. Please enter 1 or 2.\n");
        return 1;
    }

    if (choice != 1 && choice != 2)
    {
        printf("Invalid choice. Please run the program again and enter 1 or 2.\n");
        return 1;
    }

    printf("\nGenerated pattern:\n\n");

    if (choice == 1)
    {
        for (int row = 1; row <= size; row++)
        {
            for (int column = 1; column <= row; column++)
            {
                printf("* ");
            }
            printf("\n");
        }
    }
    else
    {
        for (int row = 1; row <= size; row++)
        {
            for (int column = 1; column <= row; column++)
            {
                printf("%d ", column);
            }
            printf("\n");
        }
    }

    return 0;
}