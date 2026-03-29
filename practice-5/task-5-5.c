#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

// Тип предиката: функция, принимающая int и возвращающая int (0/1)
typedef int (*Predicate)(int);

// Линейный поиск
int linear_search(const int *arr, size_t size, int target) {
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == target) return (int)i;
    }
    return -1;
}

// Бинарный поиск (массив должен быть отсортирован по возрастанию)
int binary_search(const int *arr, size_t size, int target) {
    int left = 0, right = (int)size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Поиск первого элемента, удовлетворяющего предикату
int find_if(const int *arr, size_t size, Predicate pred) {
    for (size_t i = 0; i < size; ++i) {
        if (pred(arr[i])) return (int)i;
    }
    return -1;
}

// Подсчёт элементов, удовлетворяющих предикату
size_t count_if(const int *arr, size_t size, Predicate pred) {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (pred(arr[i])) ++count;
    }
    return count;
}

// Проверка: все ли элементы удовлетворяют предикату
int all_of(const int *arr, size_t size, Predicate pred) {
    for (size_t i = 0; i < size; ++i) {
        if (!pred(arr[i])) return 0;
    }
    return 1;
}

// Проверка: есть ли хотя бы один элемент, удовлетворяющий предикату
int any_of(const int *arr, size_t size, Predicate pred) {
    for (size_t i = 0; i < size; ++i) {
        if (pred(arr[i])) return 1;
    }
    return 0;
}

// Проверка: ни один элемент не удовлетворяет предикату
int none_of(const int *arr, size_t size, Predicate pred) {
    for (size_t i = 0; i < size; ++i) {
        if (pred(arr[i])) return 0;
    }
    return 1;
}

// Примеры предикатов
int is_even(int x) { return x % 2 == 0; }
int is_odd(int x) { return x % 2 != 0; }
int is_greater_than_10(int x) { return x > 10; }
int is_negative(int x) { return x < 0; }
int is_positive(int x) { return x > 0; }

int main() {

    SetConsoleOutputCP(65001); // UTF-8 для вывода
SetConsoleCP(65001);
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("Массив: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    printf("\n\n");

    int target1 = 10;
    int idx = linear_search(arr, n, target1);
    printf("linear_search(%d): %s\n", target1, idx != -1 ? "найден" : "не найден");
    if (idx != -1) printf("  позиция %d\n", idx);

    int target2 = 14;
    idx = binary_search(arr, n, target2);
    printf("binary_search(%d): %s\n", target2, idx != -1 ? "найден" : "не найден");
    if (idx != -1) printf("  позиция %d\n", idx);

    int first_gt10 = find_if(arr, n, is_greater_than_10);
    printf("find_if(is_greater_than_10): первый элемент >10 на позиции %d (значение %d)\n",
           first_gt10, arr[first_gt10]);

    size_t cnt = count_if(arr, n, is_greater_than_10);
    printf("count_if(is_greater_than_10): %zu\n", cnt);

    printf("all_of(is_even): %s\n", all_of(arr, n, is_even) ? "true" : "false");
    printf("any_of(is_negative): %s\n", any_of(arr, n, is_negative) ? "true" : "false");
    printf("none_of(is_negative): %s\n", none_of(arr, n, is_negative) ? "true" : "false");

    return 0;
}
