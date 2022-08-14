import unittest

from src.domain.discipline import Discipline
from src.domain.validators_and_errors import DisciplineValidator, DisciplineRepositoryError, \
    DisciplineValidatorException
from src.repository.discipline_repository import DisciplineRepository


class DisciplineRepositoryTest(unittest.TestCase):
    def setUp(self):
        """
        Runs before any of the tests
        Used to set up the class so that tests can be run

        :return: None
        """
        self._validator = DisciplineValidator()
        self._repository = DisciplineRepository(self._validator)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._repository = None

    '''
    Define test functions (test cases) using functions named test_*
    '''

    def test__add_5_discipline_in_repository__length_5(self):
        self._repository.add_5_disciplines_in_repository()
        self.assertEqual(len(self._repository), 5)

    def test__add_discipline__valid_inputs__no_errors(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(len(self._repository), 2)

    def test__add_discipline__existing_id__exceptions_raised_and_catched(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        with self.assertRaises(DisciplineValidatorException):
            self._repository.add_discipline(Discipline(2, "4L"))

    def test__add_discipline__invalid_id__exceptions_raised_and_catched(self):
        with self.assertRaises(DisciplineValidatorException):
            self._repository.add_discipline(Discipline("g", "CL"))

    def test__add_discipline__invalid_name__exceptions_raised_and_catched(self):
        with self.assertRaises(DisciplineValidatorException):
            self._repository.add_discipline(Discipline(8, "4L"))

    def test__remove_discipline__valid_input__no_errors(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self._repository.remove_discipline("2")
        self.assertEqual(len(self._repository), 1)

    def test__remove_discipline__inexistent_id__exceptions_raised_and_catched(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        with self.assertRaises(DisciplineRepositoryError):
            self._repository.remove_discipline("3")

    def test__update_discipline__valid_input__no_errors(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self._repository.update_discipline("2", "Algebra")
        self.assertEqual(len(self._repository), 2)

    def test__update_discipline__inexistent_id__exceptions_raised_and_catched(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        with self.assertRaises(DisciplineRepositoryError):
            self._repository.update_discipline(3, "Algebra")

    def test__discipline_id_existence__existing_id__true(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(self._repository.discipline_id_existence("2"), True)

    def test__discipline_id_existence__inexisting_id__false(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(self._repository.discipline_id_existence("4"), False)

    def test__search_discipline_by_name__existing_name__true(self):
        self._repository.add_discipline(Discipline(1, "Algebra"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(len(self._repository.search_discipline_by_name("a")), 2)

    def test__search_discipline_by_name__inexisting_name__empty_list(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(self._repository.search_discipline_by_name("Algebra"), [])

    def test__search_discipline_by_id__existing_id__true(self):
        self._repository.add_discipline(Discipline(1, "Algebra"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self._repository.add_discipline(Discipline(24, "ASC"))
        self.assertEqual(len(self._repository.search_discipline_by_id("2")), 2)

    def test__search_discipline_by_id__inexisting_id__empty_list(self):
        self._repository.add_discipline(Discipline(1, "FP"))
        self._repository.add_discipline(Discipline(2, "Calculus"))
        self.assertEqual(self._repository.search_discipline_by_id("5"), [])


if __name__ == '__main__':
    unittest.main()
