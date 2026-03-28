Практика 4: Функции и указатели

**Студент:** Смирнов Артём Валерьевич
**Группа:** ИВТ-123
**Дата:** 15 января 2026 г.

Задание 4.1: Факториал (итеративно) *
Напишите функцию long long factorial(int n), которая вычисляет факториал числа с помощью
цикла.
long long factorial(int n);
// Пример использования:
printf("5! = %lld\n", factorial(5)); // 120
printf("10! = %lld\n", factorial(10)); // 3628800

### Код программы

#include <stdio.h>


long long factorial(int n) {
    if (n < 0) {
        return 0; // факториал отрицательного числа не определён
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int n;
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    printf("%d! = %lld\n", n, factorial(n));
    return 0;
}

<img width="979" height="504" alt="Снимок экрана 2026-03-28 144746" src="https://github.com/user-attachments/assets/0fa07ed3-280e-4378-9798-b1ee74e2df81" />


Задание 4.2: Факториал (рекурсивно) **
Напишите рекурсивную функцию long long factorial_rec(int n).

### Код программы

#include <stdio.h>

// Рекурсивная функция вычисления факториала
long long factorial_rec(int n) {
    if (n < 0) {
        
        return 0;
    }
    if (n == 0) {
        return 1; 
    }
    return n * factorial_rec(n - 1); 
}

int main() {
    int n;
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    printf("%d! = %lld\n", n, factorial_rec(n));
    return 0;
}

<img width="982" height="515" alt="Снимок экрана 2026-03-28 145310" src="https://github.com/user-attachments/assets/620cc2e3-29eb-411b-9af4-3d15920cb453" />


Задание 4.3: Степень числа *
Напишите функцию double power(double base, int exp), которая возводит число в целую степень
(включая отрицательную).
printf("2^10 = %.0lf\n", power(2, 10));
// 1024
printf("2^(-3) = %.3lf\n", power(2, -3)); // 0.125

### Код программы

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

<img width="977" height="510" alt="Снимок экрана 2026-03-28 145832" src="https://github.com/user-attachments/assets/e2438456-a928-4120-a220-2a722af9814e" />


Задание 4.4: Swap **
Напишите функцию void swap(int *a, int *b), которая меняет местами два числа через указатели.

### Код программы

#include <stdio.h>

// Функция обмена двух целых чисел через указатели
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    printf("Enter first number: ");
    scanf("%d", &x);
    printf("Enter second number: ");
    scanf("%d", &y);

    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After swap:  x = %d, y = %d\n", x, y);

    return 0;
}

<img width="980" height="511" alt="Снимок экрана 2026-03-28 150420" src="https://github.com/user-attachments/assets/378ebc8e-1786-4d19-b900-c1aeb61289ad" />


Задание 4.5: Максимум в массиве **
Напишите функцию int findMax(int *arr, int size), которая находит максимальный элемент
массива.
int arr[] = {5, 2, 9, 1, 7};
printf("Max: %d\n", findMax(arr, 5)); // 9

### Код программы

#include <stdio.h>

// Функция поиска максимального элемента в массиве
int findMax(int *arr, int size) {
    if (size <= 0) {
        
        return 0;
    }

    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int arr[n];
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Max: %d\n", findMax(arr, n));

    return 0;
}

<img width="980" height="509" alt="Снимок экрана 2026-03-28 150713" src="https://github.com/user-attachments/assets/a64d17d4-8522-4c3e-94f6-12b5d796af67" />


Задание 4.6: Индекс максимума **
Напишите функцию int findMaxIndex(int *arr, int size), которая возвращает индекс максималь-
ного элемента.

### Код программы

#include <stdio.h>

// Функция возвращает индекс максимального элемента массива
int findMaxIndex(int *arr, int size) {
    if (size <= 0) {
        return -1; 
    }

    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

int main() {
    
    int arr[] = {5, 2, 9, 1, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    int index = findMaxIndex(arr, size);
    printf("Max index: %d\n", index); 

    
    int n;
    printf("\nEnter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int userArr[n];
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &userArr[i]);
    }

    int userIndex = findMaxIndex(userArr, n);
    printf("Max index: %d\n", userIndex);

    return 0;
}

<img width="981" height="515" alt="Снимок экрана 2026-03-28 151412" src="https://github.com/user-attachments/assets/0d64548e-0533-44f4-97c4-5cfda10b3728" />


Задание 4.7: Длина строки **
Напишите функцию int my_strlen(char *str), которая возвращает длину строки (без использования
strlen).
printf("Length: %d\n", my_strlen("Hello")); // 5
printf("Length: %d\n", my_strlen("")); // 0
Подсказка: Строка в C заканчивается символом '\0'.

### Код программы

#include <stdio.h>

// Функция вычисления длины строки (без использования strlen)
int my_strlen(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    // Примеры из условия
    printf("Length: %d\n", my_strlen("Hello"));  // 5
    printf("Length: %d\n", my_strlen(""));       // 0
    printf("Length: %d\n", my_strlen(" "));      // 1 (пробел - символ)

    
    char str[100];
    printf("\nEnter a string: ");
    fgets(str, sizeof(str), stdin); 

    
    int len = my_strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--; 
    }

    printf("Length of \"%s\": %d\n", str, len);

    return 0;
}

<img width="977" height="510" alt="Снимок экрана 2026-03-28 151924" src="https://github.com/user-attachments/assets/1a3437da-ef9f-45d2-a8c5-2d714bed50e8" />

