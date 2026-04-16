#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int start;
    int end;
    int countDiv3 = 0;
    int countDiv5Not3 = 0;
    int sumDiv3 = 0;
    int sumDiv5Not3 = 0;

    printf("Enter the starting value of the interval: ");
    if (scanf("%d", &start) != 1)
    {
        printf("Invalid input. Please enter a whole number.\n");
        return 1;
    }

    printf("Enter the ending value of the interval: ");
    if (scanf("%d", &end) != 1)
    {
        printf("Invalid input. Please enter a whole number.\n");
        return 1;
    }

    if (start > end)
    {
        printf("Invalid interval. The starting value must be less than or equal to the ending value.\n");
        return 1;
    }

    for (int number = start; number <= end; number++)
    {
        if (number % 3 == 0)
        {
            countDiv3++;
            sumDiv3 += number;
        }
        else if (number % 5 == 0)
        {
            countDiv5Not3++;
            sumDiv5Not3 += number;
        }
    }

    printf("\nInterval analyzed: [%d, %d]\n", start, end);
    printf("Total values in the interval: %d\n", end - start + 1);

    printf("\nCategory 1: Numbers divisible by 3\n");
    printf("Count: %d\n", countDiv3);
    printf("Sum: %d\n", sumDiv3);

    printf("\nCategory 2: Numbers divisible by 5 but not by 3\n");
    printf("Count: %d\n", countDiv5Not3);
    printf("Sum: %d\n", sumDiv5Not3);

    printf("\nFinal comparison:\n");
    if (sumDiv3 > sumDiv5Not3)
    {
        printf("The sum of numbers divisible by 3 is greater.\n");
    }
    else if (sumDiv5Not3 > sumDiv3)
    {
        printf("The sum of numbers divisible by 5 but not by 3 is greater.\n");
    }
    else
    {
        printf("The two sums are equal.\n");
    }

    return 0;
}