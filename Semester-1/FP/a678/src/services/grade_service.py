import random

from src.domain.grade import Grade
from src.domain.validators_and_errors import StudentRepositoryError, DisciplineRepositoryError


class GradeService:
    def __init__(self, grade_repository, student_repository, discipline_repository):
        self.__grade_repository = grade_repository
        self.__student_repository = student_repository
        self.__discipline_repository = discipline_repository

    def add_grade(self, discipline_id, student_id, grade_value):
        if not self.__discipline_repository.discipline_id_existence(discipline_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_id} does not exist!")
        if not self.__student_repository.student_id_existence(student_id):
            raise StudentRepositoryError(f"Student with id={student_id} does not exist!")
        grade = Grade(discipline_id, student_id, grade_value)
        self.__grade_repository.add_grade(grade)

    def remove_grade(self, discipline_id, student_id):
        if not self.__discipline_repository.discipline_id_existence(discipline_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_id} does not exist!")
        if not self.__student_repository.student_id_existence(student_id):
            raise StudentRepositoryError(f"Student with id={student_id} does not exist!")
        grade = Grade(discipline_id, student_id, 10)
        self.__grade_repository.remove_grade(grade)

    def add_grades_in_repository(self):
        for discipline in self.__discipline_repository:
            for student in self.__student_repository:
                self.add_grade(discipline.discipline_id, student.student_id, random.randint(4, 10))

    def remove_grades_discipline(self, discipline_id):
        self.__grade_repository.remove_grades_discipline(discipline_id)

    def remove_grades_student(self, student_id):
        self.__grade_repository.remove_grades_student(student_id)

    def list_failing_students(self):
        set_failing_students = set()
        for student in self.__student_repository:
            for discipline in self.__discipline_repository:
                grades = self.__grade_repository.get_grades_student_discipline(student.student_id,
                                                                               discipline.discipline_id)
                average = 0
                for grade in grades:
                    average += grade
                if len(grades) > 0:
                    average //= len(grades)
                if average < 5:
                    set_failing_students.add(str(student))
        return set_failing_students

    def list_students_descending_averages(self):
        list_best_students = list()
        for student in self.__student_repository:
            aggregated_average = 0
            i = 0
            for discipline in self.__discipline_repository:
                grades = self.__grade_repository.get_grades_student_discipline(student.student_id,
                                                                               discipline.discipline_id)
                average = 0
                for grade in grades:
                    average += grade
                if len(grades) > 0:
                    i += 1
                    average //= len(grades)
                aggregated_average += average
            if i > 0:
                aggregated_average //= i
            list_best_students.append((aggregated_average, str(student)))
        return sorted(list_best_students, reverse=True)

    def list_disciplines_descending_averages(self):
        list_best_disciplines = list()
        for discipline in self.__discipline_repository:
            aggregated_average = 0
            i = 0
            for student in self.__student_repository:
                grades = self.__grade_repository.get_grades_student_discipline(student.student_id,
                                                                               discipline.discipline_id)
                average = 0
                for grade in grades:
                    average += grade
                if len(grades) > 0:
                    i += 1
                    average //= len(grades)
                    aggregated_average += average
            if i > 0:
                aggregated_average //= i
                list_best_disciplines.append((aggregated_average, str(discipline)))
        # return sorted(list_best_disciplines, reverse=True)
        list_best_disciplines = sorted(list_best_disciplines, reverse=True)
        list_string_best_disciplines = []
        for discipline in list_best_disciplines:
            list_string_best_disciplines.append(discipline[1])
        return list_string_best_disciplines

    def get_all_str(self):
        return self.__grade_repository.get_all_str()

    def get_all_grades(self):
        return self.__grade_repository.get_all_grades()

    def __iter__(self):
        return iter(self.__grade_repository)
