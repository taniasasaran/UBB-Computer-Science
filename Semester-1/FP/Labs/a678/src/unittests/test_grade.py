import unittest

from src.domain.grade import Grade


class GradeTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._grade = Grade(4, 6, 10)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__discipline_id_getter(self):
        self.assertEqual(self._grade.discipline_id, "4")

    def test__student_id_getter(self):
        self.assertEqual(self._grade.student_id, "6")

    def test__grade_value_getter(self):
        self.assertEqual(self._grade.grade_value, 10)

    def test__str__grade__its_string_representation(self):
        assert str(self._grade) == "Discipline_ID: 4 Student_ID: 6 GradeValue: 10"


if __name__ == '__main__':
    unittest.main()
