#include <stdio.h>


double power(double base, int exp) {
    if (exp == 0) {
        return 1.0;
    }

    int absExp = exp > 0 ? exp : -exp;
    double result = 1.0;

    
    for (int i = 0; i < absExp; i++) {
        result *= base;
    }

    
    if (exp < 0) {
        
        if (result == 0.0) {
            return 0.0; 
        }
        result = 1.0 / result;
    }

    return result;
}

int main() {
    printf("2^10 = %.0lf\n", power(2, 10));    // 1024
    printf("2^(-3) = %.3lf\n", power(2, -3));   // 0.125
    printf("5^0 = %.0lf\n", power(5, 0));       // 1
    printf("0^5 = %.0lf\n", power(0, 5));       // 0
    printf("0^(-3) = %.0lf\n", power(0, -3));   // 0 
    return 0;
}
