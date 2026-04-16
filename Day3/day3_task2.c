int main() {
    int start, end;
    int evenCount = 0, oddCount = 0;
    int evenSum = 0, oddSum = 0;

    printf("Enter start of interval: ");
    scanf("%d", &start);

    printf("Enter end of interval: ");
    scanf("%d", &end);

    // Kontroll i intervalit
    if(start > end) {
        printf("Invalid interval\n");
        return 0;
    }

    // Loop për analizë
    for(int i = start; i <= end; i++) {
        if(i % 2 == 0) {
            evenCount++;
            evenSum += i;
        } else {
            oddCount++;
            oddSum += i;
        }
    }

    int total = (end - start + 1);

    printf("\n--- RESULT ---\n");
    printf("Interval: %d to %d\n", start, end);
    printf("Total numbers: %d\n", total);

    printf("Even numbers count: %d\n", evenCount);
    printf("Odd numbers count: %d\n", oddCount);

    printf("Sum of even numbers: %d\n", evenSum);
    printf("Sum of odd numbers: %d\n", oddSum);

    // Kush ka më shumë
    if(evenCount > oddCount) {
        printf("More even numbers\n");
    } else if(oddCount > evenCount) {
        printf("More odd numbers\n");
    } else {
        printf("Equal number of even and odd\n");
    }

    return 0;
}