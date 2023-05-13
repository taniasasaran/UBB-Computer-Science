import unittest
from src.domain.discipline import Discipline
from src.domain.grade import Grade
from src.domain.student import Student


class DisciplineTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._discipline = Discipline(5, "FP")

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__discipline_id_getter(self):
        self.assertEqual(self._discipline.discipline_id, "5")

    def test__discipline_name_getter(self):
        self.assertEqual(self._discipline.name, "FP")

    def test__discipline_name_setter(self):
        self._discipline.name = "CL"
        self.assertEqual(self._discipline.name, "CL")

    def test__str__student__its_string_representation(self):
        assert str(self._discipline) == "ID: 5 NAME: FP"


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
