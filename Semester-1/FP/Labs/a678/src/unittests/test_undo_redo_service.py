import unittest

from src.domain.discipline import Discipline
from src.domain.student import Student
from src.domain.validators_and_errors import DisciplineValidator, GradeValidator, StudentValidator
from src.repository.discipline_repository import DisciplineRepository
from src.repository.grade_repository import GradeRepository
from src.repository.student_repository import StudentRepository
from src.services.discipline_service import DisciplineService
from src.services.student_service import StudentService
from src.services.undo_redo_service import UndoRedoManager
from src.services.grade_service import GradeService


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
