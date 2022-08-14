import unittest

from src.domain.grade import Grade
from src.domain.validators_and_errors import GradeValidator, GradeValidatorException
from src.repository.grade_repository import GradeRepository


class GradeRepositoryTest(unittest.TestCase):
    def setUp(self):
        """
        Runs before any of the tests
        Used to set up the class so that tests can be run

        :return: None
        """
        self._validator = GradeValidator()
        self._repository = GradeRepository(self._validator)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._repository = None

    def test__add_grade__valid_inputs__no_errors(self):
        self._repository.add_grade(Grade(1, 2, 10))
        self._repository.add_grade(Grade(2, 8, 9))
        self.assertEqual(len(self._repository), 2)

    def test__add_grade__invalid_grade__exceptions_raised_and_catched(self):
        with self.assertRaises(GradeValidatorException):
            self._repository.add_grade(Grade(1, 2, 0))


if __name__ == '__main__':
    unittest.main()

