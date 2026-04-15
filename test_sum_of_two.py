from main import sum_of_two
import unittest


class TestSumOfTwo(unittest.TestCase):

    def test_teacher_1(self):
        self.assertEqual(sum_of_two([2, 7, 11, 15], 9), [0, 1])

    def test_teacher_2(self):
        self.assertEqual(sum_of_two([3, 2, 4], 6), [1, 2])

    def test_teacher_3(self):
        self.assertEqual(sum_of_two([3, 3], 6), [0, 1])

    def test_corner_1(self):
        self.assertEqual(sum_of_two([3, 4], 6), [])

    def test_corner_2(self):
        self.assertEqual(sum_of_two([4, 4], 8), [0, 1])

    # def test_split(self):
    #     s = 'hello world'
    #     self.assertEqual(s.split(), ['hello', 'world'])
    #     # check that s.split fails when the separator is not a string
    #     with self.assertRaises(TypeError):
    #         s.split(2)


if __name__ == '__main__':
    unittest.main()
