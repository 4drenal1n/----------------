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
