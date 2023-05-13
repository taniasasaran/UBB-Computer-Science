import random

from src.domain.grade import Grade
from src.domain.validators_and_errors import StudentRepositoryError, DisciplineRepositoryError
from src.services.filter import less_than_5, filter_function
from src.services.sort import bingo_sort, is_greater_than


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
        for discipline in self.__discipline_repository.data:
            for student in self.__student_repository.data:
                self.add_grade(discipline.discipline_id, student.student_id, random.randint(3, 10))

    def remove_grades_discipline(self, discipline_id):
        self.__grade_repository.remove_grades_discipline(discipline_id)

    def remove_grades_student(self, student_id):
        self.__grade_repository.remove_grades_student(student_id)

    def list_failing_students(self):
        list_failing_students = list()
        for student in self.__student_repository.data:
            list_of_averages = list()
            for discipline in self.__discipline_repository.data:
                grades = self.__grade_repository.get_grades_student_discipline(student.student_id,
                                                                               discipline.discipline_id)
                average = 0
                for grade in grades:
                    average += grade
                if len(grades) > 0:
                    average //= len(grades)
                list_of_averages.append(average)
            if filter_function(list_of_averages, less_than_5):
                list_failing_students.append(str(student))
        return list_failing_students

    def list_students_descending_averages(self):
        list_best_students = list()
        for student in self.__student_repository.data:
            aggregated_average = 0
            i = 0
            for discipline in self.__discipline_repository.data:
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
            list_best_students.append([aggregated_average, str(student)])
        return bingo_sort(list_best_students, is_greater_than)

    def list_disciplines_descending_averages(self):
        list_best_disciplines = list()
        for discipline in self.__discipline_repository.data:
            aggregated_average = 0
            i = 0
            for student in self.__student_repository.data:
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
                list_best_disciplines.append([aggregated_average, str(discipline)])
        list_best_disciplines = bingo_sort(list_best_disciplines, is_greater_than)
        # list_string_best_disciplines = []
        # for discipline in list_best_disciplines:
        #     list_string_best_disciplines.append(discipline[1])
        # return list_string_best_disciplines
        return list_best_disciplines

    def get_all_str(self):
        return self.__grade_repository.get_all_str()

    def get_all_grades(self):
        return self.__grade_repository.get_all_grades()

    def __iter__(self):
        return iter(self.__grade_repository)
