from src.domain.validators_and_errors import StudentValidator, GradeValidator, DisciplineValidator
from src.repository.student_repository import StudentRepository
from src.repository.grade_repository import GradeRepository
from src.repository.discipline_repository import DisciplineRepository
from src.services.student_service import StudentService
from src.services.grade_service import GradeService
from src.services.discipline_service import DisciplineService
from src.services.undo_redo_service import UndoRedoManager
from src.ui.console_2 import Console


def main():
    """
    This is the main function of the program.
    :return: None
    """
    grade_validator = GradeValidator()
    grade_repository = GradeRepository(grade_validator)

    student_validator = StudentValidator()
    student_repository = StudentRepository(student_validator)
    student_repository.add_20_students_in_repository()
    student_service = StudentService(student_repository)

    discipline_validator = DisciplineValidator()
    discipline_repository = DisciplineRepository(discipline_validator)
    discipline_repository.add_5_disciplines_in_repository()
    discipline_service = DisciplineService(discipline_repository)

    grade_service = GradeService(grade_repository, student_repository, discipline_repository)
    grade_service.add_grades_in_repository()

    undo_service = UndoRedoManager(student_service, discipline_service, grade_service)

    console = Console(student_service, discipline_service, grade_service, undo_service)

    console.start()


if __name__ == '__main__':
    main()
