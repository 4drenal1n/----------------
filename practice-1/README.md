# Практическая работа 1: Установка среды и первые программы


**Студент:** Смирнов Артём Валерьевич
**Группа:** ИВТ-123
**Дата:** 15 января 2026 г.

Задание 1.1: Hello с вашим именем *
Модифицируйте программу hello.c, чтобы она выводила:
Hello! My name is [Ваше имя].
I am learning C programming.

### Код программы

#include <stdio.h>

int main(void) {
    printf("Hello, My name is Artem.\nI am learning C programming.");
    return 0;
}

Задание 1.2: Сумма двух чисел *
Скомпилируйте и запустите программу sum.c. Проверьте на примерах:
• 5 + 3 = 8
• -10 + 25 = 15
• 0 + 0 = 0

### Код программы

#include <stdio.h>

int main(void){
    int a, b, sum;

    printf("Enter first number");
    scanf("%d", &a);

    printf("Enter second number");
    scanf("%d", &b);

    sum = a+b;

    printf("Sum: %d+%d=%d\n", a, b, sum);

    return 0;
}

Задание 1.3: Произведение двух чисел *
Напишите программу multiply.c, которая:
1 Запрашивает два целых числа
2 Вычисляет их произведение
3 Выводит результат в формате: Product: A * B = C

### Код программы

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

Задание 1.4: Площадь круга **
Напишите программу circle.c, которая:
1 Запрашивает радиус круга (дробное число)
2 Вычисляет площадь по формуле S = πr²
3 Выводит результат с двумя знаками после запятой

### Код программы

#include <stdio.h>

int main() {
    double radius, area;

    printf("Enter radius: ");
    scanf("%lf", &radius);

    area = 3.14159 * radius * radius;

    printf("Area: %.2lf\n", area);

    return 0;
}

Задание 1.5: Конвертер температуры **
Напишите программу temperature.c, которая переводит температуру из Цельсия в Фаренгейт:
9
= × + 32
5

### Код программы

#include <stdio.h>

int main() {
    double C, F;

    printf("Enter temperature in Celsius: ");
    scanf("%lf", &C);

    F = C * 9 / 5 + 32;

    printf("Temperature in Fahrenheit: %.2lf\n", F);

    return 0;
}
