import unittest

from src.domain.validators_and_errors import DisciplineValidator, GradeValidator, StudentValidator, \
    DisciplineRepositoryError, DisciplineValidatorException
from src.repository.discipline_repository import DisciplineRepository
from src.repository.grade_repository import GradeRepository
from src.repository.student_repository import StudentRepository
from src.services.discipline_service import DisciplineService
from src.services.grade_service import GradeService


class DisciplineServiceTest(unittest.TestCase):
    def setUp(self):
        """
        Runs before any of the tests
        Used to set up the class so that tests can be run

        :return: None
        """
        self._discipline_validator = DisciplineValidator()
        self._grade_validator = GradeValidator()
        self._discipline_repository = DisciplineRepository(self._discipline_validator)
        self._grade_repository = GradeRepository(self._grade_validator)
        self._discipline_service = DisciplineService(self._discipline_repository)
        self._student_validator = StudentValidator()
        self._student_repository = StudentRepository(self._student_validator)
        self._grade_service = GradeService(self._grade_repository, self._student_repository,
                                           self._discipline_repository)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._discipline_service = None

    '''
    Define test functions (test cases) using functions named test_*
    '''

    def test__add_discipline__valid_inputs__no_errors(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self.assertEqual(len(self._discipline_repository), 2)

    def test__add_discipline__existing_id__exceptions_raised_and_catched(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        with self.assertRaises(DisciplineRepositoryError):
            self._discipline_service.add_discipline(24, "Algebra")

    def test__add_discipline__invalid_id__exceptions_raised_and_catched(self):
        with self.assertRaises(DisciplineValidatorException):
            self._discipline_service.add_discipline("id", "Algebra")

    def test__add_discipline__invalid_name__exceptions_raised_and_catched(self):
        with self.assertRaises(DisciplineValidatorException):
            self._discipline_service.add_discipline(44, "12gd6")

    def test__remove_discipline__valid_input__no_errors(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self._discipline_service.remove_discipline("22")
        self.assertEqual(len(self._discipline_repository), 1)

    def test__remove_discipline__inexisting_id__exceptions_raised_and_catched(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        with self.assertRaises(DisciplineRepositoryError):
            self._discipline_service.remove_discipline("3")

    def test__update_discipline__valid_input__no_errors(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self._discipline_service.update_discipline("24", "ASC")
        self.assertEqual(len(self._discipline_repository), 2)

    def test__update_discipline__inexisting_id__exceptions_raised_and_catched(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        with self.assertRaises(DisciplineRepositoryError):
            self._discipline_service.update_discipline("1", "Algebra")

    def test__remove_discipline(self):
        self._student_repository.add_20_students_in_repository()
        self._discipline_repository.add_5_disciplines_in_repository()
        self._discipline_service.add_discipline(24, "discipline")
        self._grade_service.add_grades_in_repository()
        self._discipline_service.remove_discipline("24")
        self.assertEqual(len(self._grade_repository), 120)

    def test__get_all(self):
        self._discipline_repository.add_5_disciplines_in_repository()
        self.assertEqual(len(self._grade_service.get_all_str()), len(self._grade_repository))

    def test__search_discipline_by_name__existing_name__true(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "Algebra")
        self.assertEqual(len(self._discipline_service.search_discipline_by_name("l")), 2)

    def test__search_discipline_by_name__inexisting_name__empty_list(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self.assertEqual(self._discipline_service.search_discipline_by_name("Algebra"), [])

    def test__search_discipline_by_id__existing_id__true(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self.assertEqual(len(self._discipline_service.search_discipline_by_id("2")), 2)

    def test__search_discipline_by_id__inexisting_id__empty_list(self):
        self._discipline_service.add_discipline(24, "CL")
        self._discipline_service.add_discipline(22, "FP")
        self.assertEqual(self._discipline_service.search_discipline_by_id("5"), [])


if __name__ == '__main__':
    unittest.main()
