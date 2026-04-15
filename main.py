"""
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
"""


def sum_of_two(nums: list, target: int) -> list:
    seen = {}
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []


if __name__ == "__main__":
    nums_input = input("Enter numbers separated by spaces (e.g., 2 7 11 15): ")
    target_input = input("Enter target value: ")

    nums = list(map(int, nums_input.split()))
    target = int(target_input)

    result = sum_of_two(nums, target)

    if result:
        print(f"Indices: {result}")
    else:
        print("No solution found")
