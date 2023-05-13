import unittest

from src.domain.discipline import Discipline
from src.domain.student import Student
from src.domain.validators_and_errors import DisciplineValidator, GradeValidator, StudentValidator, \
    DisciplineRepositoryError, StudentRepositoryError, GradeValidatorException
from src.repository.discipline_repository import DisciplineRepository
from src.repository.grade_repository import GradeRepository
from src.repository.student_repository import StudentRepository
from src.services.grade_service import GradeService


class GradeServiceTest(unittest.TestCase):
    def setUp(self):
        """
        Runs before any of the tests
        Used to set up the class so that tests can be run

        :return: None
        """
        self._discipline_validator = DisciplineValidator()
        self._grade_validator = GradeValidator()
        self._student_validator = StudentValidator()

        self._discipline_repository = DisciplineRepository(self._discipline_validator)
        self._grade_repository = GradeRepository(self._grade_validator)
        self._student_repository = StudentRepository(self._student_validator)

        self._grade_service = GradeService(self._grade_repository, self._student_repository,
                                           self._discipline_repository)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._grade_service = None

    '''
    Define test functions (test cases) using functions named test__*
    '''

    def test__add_grade__valid_inputs__no_errors(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("4", "5", 10)
        self._grade_service.add_grade("3", "19", 9)
        self.assertEqual(len(self._grade_repository), 2)

    def test__add_grade__invalid_grade__exceptions_raised_and_catched(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("1", "5", 10)
        self._grade_service.add_grade("2", "20", 10)
        with self.assertRaises(GradeValidatorException):
            self._grade_service.add_grade("2", "20", 99)

    def test__add_grade__inexistent_student_id__exceptions_raised_and_catched(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("1", "5", 10)
        self._grade_service.add_grade("2", "20", 10)
        with self.assertRaises(StudentRepositoryError):
            self._grade_service.add_grade("2", "55", 9)

    def test__add_grade__inexistent_discipline_id__exceptions_raised_and_catched(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("1", "5", 10)
        self._grade_service.add_grade("2", "20", 10)
        with self.assertRaises(DisciplineRepositoryError):
            self._grade_service.add_grade("7", "5", 9)

    def test__remove_grade__valid_input__no_errors(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("4", "5", 10)
        self._grade_service.add_grade("3", "19", 9)
        self._grade_service.remove_grade("4", "5")
        self.assertEqual(len(self._grade_repository), 1)

    def test__remove_grade__inexistent_discipline_id__exceptions_raised_and_catched(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grade("4", "5", 10)
        self._grade_service.add_grade("3", "19", 9)
        with self.assertRaises(DisciplineRepositoryError):
            self._grade_service.remove_grade("8", "5")

    def test__add_grades_in_repository(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grades_in_repository()
        self.assertEqual(len(self._grade_repository), 100)

    def test__list_students_descending_averages(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grades_in_repository()
        self.assertEqual(len(self._grade_service.list_students_descending_averages()), len(self._student_repository))

    def test__list_disciplines_descending_averages(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grades_in_repository()
        self.assertEqual(len(self._grade_service.list_disciplines_descending_averages()),
                         len(self._discipline_repository))

    def test__get_all(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grades_in_repository()
        self.assertEqual(len(self._grade_service.get_all_str()), len(self._grade_repository))

    def test__list_failing_students(self):
        self._student_repository.add_student(Student(1, "Tania"))
        self._student_repository.add_student(Student(3, "Ava"))
        self._student_repository.add_student(Student(20, "John"))
        self._discipline_repository.add_discipline(Discipline(1, "FP"))
        self._discipline_repository.add_discipline(Discipline(2, "CL"))
        self._grade_service.add_grade("1", "1", 3)
        self._grade_service.add_grade("2", "1", 10)
        self._grade_service.add_grade("2", "20", 4)
        self._grade_service.add_grade("1", "20", 3)
        self._grade_service.add_grade("1", "3", 5)
        self._grade_service.add_grade("2", "3", 7)
        self.assertEqual(len(self._grade_service.list_failing_students()), 2)


if __name__ == '__main__':
    unittest.main()
