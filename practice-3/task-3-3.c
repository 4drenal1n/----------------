#include <stdio.h>

int main() {
    int n;

    printf("Enter N: ");
    scanf("%d", &n);

    if (n <= 0) {
        
        return 0;
    }

    long long a = 0, b = 1, next;
    printf("Fibonacci:");
    for (int i = 0; i < n; i++) {
        printf(" %lld", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");

    return 0;
}
