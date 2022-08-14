import unittest

from src.domain.student import Student


class StudentTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._student = Student(5, "Tania")

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__student_id_getter(self):
        self.assertEqual(self._student.student_id, "5")

    def test__student_name_getter(self):
        self.assertEqual(self._student.name, "Tania")

    def test__student_name_setter(self):
        self._student.name = "Nume"
        self.assertEqual(self._student.name, "Nume")

    def test__str__student__its_string_representation(self):
        assert str(self._student) == "ID: 5 NAME: Tania"


if __name__ == '__main__':
    unittest.main()
