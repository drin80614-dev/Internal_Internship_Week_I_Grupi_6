#include <stdio.h>

int main(void) {
    char name[] = "Egli Shaljani";
    int age = 16;
    char school[] = "British Gymnasium of Technology";
    char className[] = "XI-3";
    char interest[] = "Software Development";

    printf("-------------------------------------\n");
    printf("           STUDENT PROFILE\n");
    printf("-------------------------------------\n");
    printf("Name      : %s\n", name);
    printf("Age       : %d\n", age);
    printf("School    : %s\n", school);
    printf("Class     : %s\n", className);
    printf("Interest  : %s\n", interest);

    return 0;
}