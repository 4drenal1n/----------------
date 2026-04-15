# Сумма двух (Two Sum)

## Описание задачи

Дан массив целых чисел `nums` и целочисленное значение переменной `target`. Необходимо вернуть индексы двух чисел таким образом, чтобы они в сумме давали `target`. 

У каждого входного набора может не быть решений и может быть только одно решение. Нельзя использовать один и тот же элемент дважды.

## Примеры

**Example 1:**
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
```

**Example 2:**
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
```

**Example 3:**
```
Input: nums = [3,3], target = 6
Output: [0,1]
```

## Алгоритм

Используется хэш-таблица (словарь) для хранения уже пройденных элементов. Для каждого элемента вычисляется дополнение (`complement = target - num`). Если дополнение найдено в словаре, возвращается пара индексов. 


### Результат тестов

test_corner_1 (test_sum_of_two.TestSumOfTwo.test_corner_1) ... ok
test_corner_2 (test_sum_of_two.TestSumOfTwo.test_corner_2) ... ok
test_teacher_1 (test_sum_of_two.TestSumOfTwo.test_teacher_1) ... ok
test_teacher_2 (test_sum_of_two.TestSumOfTwo.test_teacher_2) ... ok
test_teacher_3 (test_sum_of_two.TestSumOfTwo.test_teacher_3) ... ok

