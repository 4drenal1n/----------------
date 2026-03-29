#include <stdio.h>
#include <stdlib.h>


typedef int (*Transform)(int);
typedef int (*Predicate)(int);
typedef int (*Reducer)(int, int);
typedef void (*Action)(int, size_t);

void array_map(int *arr, size_t size, Transform func) {
    for (size_t i = 0; i < size; ++i)
        arr[i] = func(arr[i]);
}

size_t array_filter(const int *src, size_t size, int *dst, Predicate pred) {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i)
        if (pred(src[i]))
            dst[count++] = src[i];
    return count;
}

int array_reduce(const int *arr, size_t size, int initial, Reducer func) {
    int result = initial;
    for (size_t i = 0; i < size; ++i)
        result = func(result, arr[i]);
    return result;
}

void array_foreach(const int *arr, size_t size, Action act) {
    for (size_t i = 0; i < size; ++i)
        act(arr[i], i);
}

// Трансформеры
int square(int x) { return x * x; }
int negate(int x) { return -x; }
int double_val(int x) { return x * 2; }
int abs_val(int x) { return x < 0 ? -x : x; }

// Предикаты
int is_even(int x) { return x % 2 == 0; }
int is_positive(int x) { return x > 0; }
int is_greater_than_10(int x) { return x > 10; }

// Редьюсеры
int sum(int a, int b) { return a + b; }
int product(int a, int b) { return a * b; }
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

void print_element(int x, size_t idx) {
    printf("arr[%zu] = %d\n", idx, x);
}

int main() {
    
    int arr[] = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    printf("Original: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    putchar('\n');

    // Map
    array_map(arr, n, square);
    printf("After map(square): ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    putchar('\n');

    // Filter
    int filtered[10];
    size_t filtered_cnt = array_filter(arr, n, filtered, is_positive);
    printf("After filter(is_positive): ");
    for (size_t i = 0; i < filtered_cnt; ++i) printf("%d ", filtered[i]);
    putchar('\n');

    // Reduce
    int total = array_reduce(filtered, filtered_cnt, 0, sum);
    printf("Reduce(sum, 0): %d\n", total);

    // ForEach
    printf("ForEach:\n");
    array_foreach(filtered, filtered_cnt, print_element);

    return 0;
}
