#include <stdio.h>

int main() {
    int a, b, product;

    // Запрос двух целых чисел
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    // Вычисление произведения
    product = a * b;

    // Вывод результата в требуемом формате
    printf("Product: %d * %d = %d\n", a, b, product);

    return 0;
}
