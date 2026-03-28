#include <stdio.h>
#include <math.h>

typedef struct {
    double min;
    double max;
    double sum;
    double average;
    double variance; // дисперсия
} ArrayStats;

ArrayStats calculate_stats(const double *arr, size_t size) {
    ArrayStats stats = {0.0, 0.0, 0.0, 0.0, 0.0};

    if (size == 0 || arr == NULL) {
        return stats; // пустой массив – все поля нулевые
    }

    stats.min = stats.max = arr[0];
    stats.sum = arr[0];

    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < stats.min) stats.min = arr[i];
        if (arr[i] > stats.max) stats.max = arr[i];
        stats.sum += arr[i];
    }

    stats.average = stats.sum / size;

    double sum_sq_diff = 0.0;
    for (size_t i = 0; i < size; ++i) {
        double diff = arr[i] - stats.average;
        sum_sq_diff += diff * diff;
    }
    stats.variance = sum_sq_diff / size;

    return stats;
}

int main() {
    double arr[] = {2.5, 4.0, 1.5, 3.0, 5.0};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    ArrayStats s = calculate_stats(arr, n);

    printf("Min: %.2f, Max: %.2f\n", s.min, s.max);
    printf("Sum: %.2f, Average: %.2f\n", s.sum, s.average);
    printf("Variance: %.2f\n", s.variance);

    return 0;
}
