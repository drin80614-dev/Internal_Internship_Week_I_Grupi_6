

int main() {
    int num, oldNum;
    double price;
    int *pNum;
    double *pPrice;

    printf("Enter an integer value: ");
    scanf("%d", &num);

    printf("Enter a double value: ");
    scanf("%lf", &price);

    oldNum = num;

    pNum = &num;
    pPrice = &price;

    printf("\n--- BEFORE CHANGE ---\n");
    printf("Direct int value: %d\n", num);
    printf("Direct double value: %.2lf\n", price);

    printf("Address of int: %p\n", (void*)&num);
    printf("Address of double: %p\n", (void*)&price);

    printf("Value of int through pointer: %d\n", *pNum);
    printf("Value of double through pointer: %.2lf\n", *pPrice);

    *pNum = *pNum + 10;

    printf("\n--- AFTER CHANGE ---\n");
    printf("Old int value: %d\n", oldNum);
    printf("New int value: %d\n", num);

    if (num > oldNum) {
        printf("Final message: value increased\n");
    } else if (num < oldNum) {
        printf("Final message: value decreased\n");
    } else {
        printf("Final message: value stayed the same\n");
    }

    if (num >= 0 && num <= 50) {
        printf("Range check: final value is between 0 and 50\n");
    } else {
        printf("Range check: final value is outside 0 to 50\n");
    }

    return 0;
}