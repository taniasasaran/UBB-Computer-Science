import unittest
import random

from src.repository.iterable_structure import Collection, Instance
from src.services.filter import less_than_5, filter_function
from src.services.sort import bingo_sort, is_less_than, is_greater_than


class SortTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._array = [[i, "string"] for i in range(4, 10)]
        random.shuffle(self._array)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_sort__is_less_than(self):
        self._array = bingo_sort(self._array, is_less_than)
        self.assertEqual(self._array, [[4, 'string'], [5, 'string'], [6, 'string'], [7, 'string'], [8, 'string'], [9, 'string']])

    def test_sort__is_greater_than(self):
        self._array = bingo_sort(self._array, is_greater_than)
        self.assertEqual(self._array, [[9, 'string'], [8, 'string'], [7, 'string'], [6, 'string'], [5, 'string'], [4, 'string']])


class FilterTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._list = []
        self._acceptance_function = less_than_5

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test_filter__less_than_5__list_of_values_greater_than_5__empty_list(self):
        self._list = [x for x in range(7, 20)]
        self._list = filter_function(self._list, self._acceptance_function)
        self.assertEqual(self._list, [])

    def test_filter__less_than_5__list_with_5_values_less_than_5__5_values(self):
        self._list = [x for x in range(10)]
        self._list = filter_function(self._list, self._acceptance_function)
        self.assertEqual(self._list, [0, 1, 2, 3, 4])

    def test_filter__less_than_5__list_2_values_less_than_5__2_values(self):
        self._list = [2, 7, 24, 4, 5, 28]
        self._list = filter_function(self._list, self._acceptance_function)
        self.assertEqual(self._list, [2, 4])


class IterableStructureTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._collection = Collection()

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__add_item(self):
        self._collection.__add__(Instance(24, "nume1"))
        self._collection.__add__(Instance(28, "nume2"))
        self.assertEqual(len(self._collection), 2)

    def test__get_item(self):
        self._collection.__add__(Instance(24, "nume1"))
        self._collection.__add__(Instance(28, "nume2"))
        self.assertEqual(self._collection[0].id, '24')

    def test__del_item(self):
        self._collection.__add__(Instance(24, "nume1"))
        self._collection.__add__(Instance(28, "nume2"))
        self._collection.__delitem__(1)
        self.assertEqual(len(self._collection), 1)

    def test__set_name(self):
        self._collection.__add__(Instance(24, "nume1"))
        self._collection.__add__(Instance(28, "nume2"))
        self._collection.__setitem__(0, "nume")
        self.assertEqual(self._collection.__getitem__(0).name, "nume")

    def test__iter(self):
        self._collection.__add__(1)
        self._collection.__add__(2)
        self._collection.__add__(3)
        self.assertEqual(self._collection.__next__(), 1)
        self.assertEqual(self._collection.__next__(), 2)
        self.assertEqual(self._collection.__next__(), 3)
        with self.assertRaises(StopIteration):
            self._collection.__next__()


if __name__ == '__main__':
    unittest.main()
