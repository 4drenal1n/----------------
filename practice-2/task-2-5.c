#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, discriminant, root1, root2;

    printf("Enter a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("D = %.2lf\n", discriminant);
        printf("x1 = %.2lf\n", root1);
        printf("x2 = %.2lf\n", root2);
    }
    else if (fabs(discriminant) < 1e-9) {  // проверка на приблизительное равенство нулю
        root1 = -b / (2 * a);
        printf("D = %.2lf\n", discriminant);
        printf("x = %.2lf\n", root1);
    }
    else {
        printf("D = %.2lf\n", discriminant);
        printf("No real roots\n");
    }

    return 0;
}
