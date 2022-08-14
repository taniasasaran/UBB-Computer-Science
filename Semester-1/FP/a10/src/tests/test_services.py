import unittest

from src.domain.discipline import Discipline
from src.domain.student import Student
from src.domain.validators_and_errors import DisciplineValidator, GradeValidator, StudentValidator, \
    DisciplineRepositoryError, DisciplineValidatorException, StudentRepositoryError, GradeValidatorException, \
    StudentValidatorException
from src.repository.discipline_repository import DisciplineRepository
from src.repository.grade_repository import GradeRepository
from src.repository.student_repository import StudentRepository
from src.services.discipline_service import DisciplineService
from src.services.grade_service import GradeService
from src.services.student_service import StudentService
from src.services.undo_redo_service import UndoRedoManager


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
        # self.assertEqual(len(self._grade_repository), 1)

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


class UndoServiceTest(unittest.TestCase):
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
        self._discipline_service = DisciplineService(self._discipline_repository)
        self._grade_service = GradeService(self._grade_repository, self._student_repository,
                                           self._discipline_repository)
        self._undo_redo_service = UndoRedoManager(self._student_service, self._discipline_service, self._grade_service)

    def tearDown(self) -> None:
        """
        Runs after all the tests have completed
        Used to close the test environment (clause files, DB connections, deallocate memory)

        :return: None
        """
        self._undo_redo_service = None

    def test_add_command_to_stack(self):
        self._undo_redo_service.add_command_to_stack("addCommand", [1, 1])
        self.assertEqual(self._undo_redo_service.get_stack(), [["addCommand", [1, 1]]])

    def test_getters(self):
        self._undo_redo_service.add_command_to_stack("addCommand", [1, 1])
        self.assertEqual(self._undo_redo_service.get_last_operation(), ["addCommand", [1, 1]])
        self.assertEqual(self._undo_redo_service.get_last_operation_command(["addCommand", [1, 1]]), "addCommand")
        self.assertEqual(self._undo_redo_service.get_last_operation_object(["addCommand", [1, 1]]), [1, 1])

    def test_undo_redo_add_student(self):
        self._student_service.add_student(40, "Tania")
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])
        self._undo_redo_service.undo_add_student(Student(40, "Tania"))
        self.assertEqual(self._student_repository.get_all_str(), [])
        self._undo_redo_service.redo_add_student(Student(40, "Tania"))
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])

    def test_undo_redo_remove_student(self):
        self._student_service.add_student(40, "Tania")
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])
        self._student_service.remove_student("40")
        self.assertEqual(self._student_repository.get_all_str(), [])
        self._undo_redo_service.undo_remove_student(Student(40, "Tania"))
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])
        self._undo_redo_service.redo_remove_student(Student(40, "Tania"))
        self.assertEqual(self._student_repository.get_all_str(), [])

    def test_undo_redo_update_student(self):
        self._student_service.add_student(40, "Tania")
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])
        self._student_service.update_student('40', "Sorana")
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Sorana"))])
        self._undo_redo_service.undo_update_student(['40', "Tania", None])
        self.assertEqual(self._student_repository.get_all_str(), [str(Student(40, "Tania"))])
        self._undo_redo_service.redo_update_student(['40', None, "Sorana"])
        self._undo_redo_service.undo_update_student(['40', "Tania", None])

    def test_undo_redo_add_grade(self):
        self._discipline_service.add_discipline(7, "ASDN")
        discipline_string = str(Discipline(7, "ASDN"))
        self.assertEqual(self._discipline_repository.get_all_str(), [discipline_string])
        self._undo_redo_service.undo_add_discipline(Discipline(7, "ASDN"))
        self.assertEqual(self._discipline_repository.get_all_str(), [])
        self._undo_redo_service.redo_add_discipline(Discipline(7, "ASDN"))
        self.assertEqual(self._discipline_repository.get_all_str(), [discipline_string])



if __name__ == '__main__':
    unittest.main()
