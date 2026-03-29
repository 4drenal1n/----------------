#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef int (*Comparator)(const void*, const void*);

void bubble_sort(void *base, size_t count, size_t size, Comparator cmp) {
    for (size_t i = 0; i < count - 1; ++i) {
        for (size_t j = 0; j < count - i - 1; ++j) {
            char *a = (char*)base + j * size;
            char *b = (char*)base + (j + 1) * size;
            if (cmp(a, b) > 0) {
                // swap
                char tmp[size];
                memcpy(tmp, a, size);
                memcpy(a, b, size);
                memcpy(b, tmp, size);
            }
        }
    }
}

// Компараторы для int
int compare_int_asc(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return ia - ib;
}

int compare_int_desc(const void *a, const void *b) {
    return compare_int_asc(b, a);
}

// Компараторы для строк
int compare_str_asc(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int compare_str_length(const void *a, const void *b) {
    const char *sa = *(const char**)a;
    const char *sb = *(const char**)b;
    return (int)(strlen(sa) - strlen(sb));
}

// Структура Employee
typedef struct {
    char name[50];
    int age;
    double salary;
} Employee;

int compare_employee_by_name(const void *a, const void *b) {
    const Employee *ea = a;
    const Employee *eb = b;
    return strcmp(ea->name, eb->name);
}

int compare_employee_by_age(const void *a, const void *b) {
    const Employee *ea = a;
    const Employee *eb = b;
    return ea->age - eb->age;
}

int compare_employee_by_salary(const void *a, const void *b) {
    const Employee *ea = a;
    const Employee *eb = b;
    if (ea->salary < eb->salary) return -1;
    if (ea->salary > eb->salary) return 1;
    return 0;
}

int main() {
    SetConsoleOutputCP(65001); // UTF-8 для вывода
    SetConsoleCP(65001); // UTF-8 для ввода
    // Пример с int
    int arr[] = {5, 2, 8, 1, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n, sizeof(int), compare_int_asc);
    printf("По возрастанию: ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    putchar('\n');

    bubble_sort(arr, n, sizeof(int), compare_int_desc);
    printf("По убыванию:   ");
    for (size_t i = 0; i < n; ++i) printf("%d ", arr[i]);
    putchar('\n');

    // Пример с Employee
    Employee emps[] = {
        {"Иван", 25, 45000.0},
        {"Мария", 30, 55000.0},
        {"Пётр", 28, 60000.0}
    };
    size_t emp_count = sizeof(emps) / sizeof(emps[0]);

    bubble_sort(emps, emp_count, sizeof(Employee), compare_employee_by_salary);
    printf("\nСотрудники по зарплате:\n");
    for (size_t i = 0; i < emp_count; ++i) {
        printf("%s, %d, %.2f\n", emps[i].name, emps[i].age, emps[i].salary);
    }

    return 0;
}
