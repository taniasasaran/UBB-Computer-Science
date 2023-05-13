import unittest

from src.domain.validators_and_errors import GradeValidator, StudentValidator, DisciplineValidator, \
    StudentRepositoryError, StudentValidatorException
from src.repository.discipline_repository import DisciplineRepository
from src.repository.grade_repository import GradeRepository
from src.repository.student_repository import StudentRepository
from src.services.grade_service import GradeService
from src.services.student_service import StudentService


class StudentServiceTest(unittest.TestCase):
    def setUp(self):
        """
        Runs before any of the tests
        Used to set up the class so that tests can be run

        :return: None
        """
        self._student_validator = StudentValidator()
        self._grade_validator = GradeValidator()
        self._discipline_validator = DisciplineValidator()
        self._student_repository = StudentRepository(self._student_validator)
        self._grade_repository = GradeRepository(self._grade_validator)
        self._discipline_repository = DisciplineRepository(self._discipline_validator)
        self._student_service = StudentService(self._student_repository)
        self._grade_service = GradeService(self._grade_repository, self._student_repository,
                                           self._discipline_repository)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._student_service = None

    '''
    Define test functions (test cases) using functions named test_*
    '''

    def test__add_student__valid_inputs__no_errors(self):
        self._student_service.add_student(1, "Tania")
        self.assertEqual(len(self._student_repository), 1)

    def test__add_student__invalid_id__exceptions_raised_and_catched(self):
        with self.assertRaises(StudentValidatorException):
            self._student_service.add_student(-1, "Student")

    def test__add_student__invalid_name__exceptions_raised_and_catched(self):
        with self.assertRaises(StudentValidatorException):
            self._student_service.add_student(3, "916")

    def test__remove_student__valid_input__no_errors(self):
        self._student_service.add_student(1, "Tania")
        self._student_service.add_student(22, "Mihai")
        self._student_service.add_student(28, "Alex")
        self._student_service.add_student(14, "Adi")
        self._student_service.remove_student("28")
        self.assertEqual(len(self._student_repository), 3)

    def test__remove_student__inexistent_id__exceptions_raised_and_catched(self):
        self._student_service.add_student(1, "Tania")
        self._student_service.add_student(22, "Mihai")
        self._student_service.add_student(28, "Alex")
        self._student_service.add_student(14, "Adi")
        with self.assertRaises(StudentRepositoryError):
            self._student_service.remove_student("3")

    def test__update_student__valid_input__no_errors(self):
        self._student_service.add_student(1, "Tania")
        self._student_service.add_student(22, "Mihai")
        self._student_service.add_student(28, "Alex")
        self._student_service.update_student("28", "Traian")
        self.assertEqual(len(self._student_repository), 3)

    def test__update_student__inexistent_id__exceptions_raised_and_catched(self):
        self._student_service.add_student(24, "Tania")
        self._student_service.add_student(22, "Mihai")
        with self.assertRaises(StudentRepositoryError):
            self._student_service.update_student("1", "Traian")

    def test__remove_student(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._grade_service.add_grades_in_repository()
        self._student_service.remove_student("20")
        self.assertEqual(len(self._grade_repository), 100)

    def test__find_student_by_id__2_elements(self):
        self._student_repository.add_20_students_in_repository()
        self.assertEqual(len(self._student_service.find_student_by_id("2")), 2)

    def test__find_student_by_id__0_elements(self):
        self._student_repository.add_20_students_in_repository()
        self.assertEqual(len(self._student_service.find_student_by_id("88")), 0)

    def test__get_all(self):
        self._student_repository.add_20_students_in_repository()
        self.assertEqual(len(self._student_service.get_all_str()), len(self._student_repository))


if __name__ == '__main__':
    unittest.main()
