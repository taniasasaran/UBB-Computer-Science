from src.domain.validators_and_errors import StudentValidator, GradeValidator, DisciplineValidator
from src.repository.student_repository import StudentRepository, StudentTextFileRepository, StudentBinFileRepository
from src.repository.grade_repository import GradeRepository, GradeTextFileRepository, GradeBinFileRepository
from src.repository.discipline_repository import DisciplineRepository, DisciplineTextFileRepository, \
    DisciplineBinFileRepository
from src.services.student_service import StudentService
from src.services.grade_service import GradeService
from src.services.discipline_service import DisciplineService
from src.services.undo_redo_service import UndoRedoManager
from src.ui.console import Console

from src.properties.settings_class import Settings


def main():
    """
    This is the main function of the program.
    :return: None
    """
    student_validator = StudentValidator()
    discipline_validator = DisciplineValidator()
    grade_validator = GradeValidator()

    try:
        settings = Settings('properties/settings.properties')
    except AttributeError:
        print("Please uncomment the properties!")
        return

    if settings.repository == 'binaryfiles':
        student_repository = StudentBinFileRepository(student_validator, settings.students)
        discipline_repository = DisciplineBinFileRepository(discipline_validator, settings.disciplines)
        grade_repository = GradeBinFileRepository(grade_validator, settings.grades)
    elif settings.repository == 'textfiles':
        student_repository = StudentTextFileRepository(student_validator, settings.students)
        discipline_repository = DisciplineTextFileRepository(discipline_validator, settings.disciplines)
        grade_repository = GradeTextFileRepository(grade_validator, settings.grades)
    elif settings.repository == 'inmemory':
        student_repository = StudentRepository(student_validator)
        discipline_repository = DisciplineRepository(discipline_validator)
        grade_repository = GradeRepository(grade_validator)
    else:
        print("Please write in what form data is represented: binaryfiles, textfiles or inmemory!")
        return

    student_service = StudentService(student_repository)

    discipline_service = DisciplineService(discipline_repository)

    grade_service = GradeService(grade_repository, student_repository, discipline_repository)

    if settings.repository == 'inmemory':
        student_service.add_20_students_in_repository()
        discipline_service.add_5_disciplines_in_repository()
        grade_service.add_grades_in_repository()

    undo_service = UndoRedoManager(student_service, discipline_service, grade_service)

    console = Console(student_service, discipline_service, grade_service, undo_service)

    console.start()


if __name__ == '__main__':
    main()
