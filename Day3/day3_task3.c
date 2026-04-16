

int main() {
    int start, end;
    int count3 = 0, count5 = 0;
    int sum3 = 0, sum5 = 0;

    printf("Enter start: ");
    scanf("%d", &start);

    printf("Enter end: ");
    scanf("%d", &end);

    // Kontroll intervali
    if(start > end) {
        printf("Invalid interval\n");
        return 0;
    }

    // Loop
    for(int i = start; i <= end; i++) {

        // Numrat qe pjesetohen me 3
        if(i % 3 == 0) {
            sum3 += i;
            count3++;
        }
        // Numrat qe pjesetohen me 5 por jo me 3
        else if(i % 5 == 0) {
            sum5 += i;
            count5++;
        }
    }

    printf("\n--- RESULT ---\n");
    printf("Divisible by 3 -> Count: %d, Sum: %d\n", count3, sum3);
    printf("Divisible by 5 (not 3) -> Count: %d, Sum: %d\n", count5, sum5);

    // Krahasimi
    if(sum3 > sum5) {
        printf("Sum of numbers divisible by 3 is greater\n");
    }
    else if(sum5 > sum3) {
        printf("Sum of numbers divisible by 5 is greater\n");
    }
    else {
        printf("Both sums are equal\n");
    }

    return 0;
}