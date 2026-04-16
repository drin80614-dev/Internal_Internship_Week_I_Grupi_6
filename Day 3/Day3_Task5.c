#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
    int number;
    double decimalNumber;

    int* pNumber;
    double* pDecimal;

    int originalNumber;
    double originalDecimal;

    printf("Enter an integer value: ");
    if (scanf("%d", &number) != 1)
    {
        printf("Invalid input. Please enter a whole number.\n");
        return 1;
    }

    printf("Enter a decimal value: ");
    if (scanf("%lf", &decimalNumber) != 1)
    {
        printf("Invalid input. Please enter a decimal number.\n");
        return 1;
    }

    originalNumber = number;
    originalDecimal = decimalNumber;

    pNumber = &number;
    pDecimal = &decimalNumber;

    printf("\n----- BEFORE CHANGE -----\n");
    printf("Direct integer value: %d\n", number);
    printf("Integer address: %p\n", (void*)&number);
    printf("Integer value through pointer: %d\n", *pNumber);

    printf("\nDirect decimal value: %.2lf\n", decimalNumber);
    printf("Decimal address: %p\n", (void*)&decimalNumber);
    printf("Decimal value through pointer: %.2lf\n", *pDecimal);

    *pNumber = *pNumber + 5;
    *pDecimal = *pDecimal * 1.50;

    printf("\n----- AFTER CHANGE -----\n");
    printf("Updated integer value: %d\n", number);
    printf("Updated integer value through pointer: %d\n", *pNumber);

    printf("\nUpdated decimal value: %.2lf\n", decimalNumber);
    printf("Updated decimal value through pointer: %.2lf\n", *pDecimal);

    printf("\n----- COMPARISON FOR INTEGER -----\n");
    printf("Integer before change: %d\n", originalNumber);
    printf("Integer after change: %d\n", number);

    if (number > originalNumber)
    {
        printf("Result: The integer value increased.\n");
    }
    else if (number < originalNumber)
    {
        printf("Result: The integer value decreased.\n");
    }
    else
    {
        printf("Result: The integer value stayed the same.\n");
    }

    printf("\n----- COMPARISON FOR DECIMAL -----\n");
    printf("Decimal before change: %.2lf\n", originalDecimal);
    printf("Decimal after change: %.2lf\n", decimalNumber);

    if (decimalNumber > originalDecimal)
    {
        printf("Result: The decimal value increased.\n");
    }
    else if (decimalNumber < originalDecimal)
    {
        printf("Result: The decimal value decreased.\n");
    }
    else
    {
        printf("Result: The decimal value stayed the same.\n");
    }

    printf("\n----- FINAL RANGE CHECK -----\n");
    if (number >= 0 && number <= 50)
    {
        printf("The final integer value is inside the interval [0, 50].\n");
    }
    else
    {
        printf("The final integer value is outside the interval [0, 50].\n");
    }

    return 0;
}