#include <stdio.h>

int main() {
    double C, F;

    printf("Enter temperature in Celsius: ");
    scanf("%lf", &C);

    F = C * 9 / 5 + 32;

    printf("Temperature in Fahrenheit: %.2lf\n", F);

    return 0;
}
