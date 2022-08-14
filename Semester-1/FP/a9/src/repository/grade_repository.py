import json
import pickle
from copy import deepcopy

from src.domain.grade import Grade
from src.domain.validators_and_errors import GradeRepositoryError


class GradeRepository:
    def __init__(self, grade_validator_class):
        self.__validator_class = grade_validator_class
        self.data = list()

    def add_grade(self, grade):
        """
            This function adds a grade in the repository
            :param grade: an object(class)
            :return: none
        """
        self.__validator_class.validate(grade)
        self.data.append(grade)

    def remove_grade(self, grade_to_be_removed):
        """
        This function removes the grade
        :param grade_to_be_removed: an object(class)
        :return: None
        """
        for i, grade in reversed(list(enumerate(self.data))):
            if grade.student_id == grade_to_be_removed.student_id and \
                    grade.discipline_id == grade_to_be_removed.discipline_id:
                del self.data[i]
                break

    def get_grades_student_discipline(self, student_id, discipline_id):
        """
        This function creates a list of all the grades of a student at a certain discipline
        :param student_id: string
        :param discipline_id: string
        :return: list of integers
        """
        grades_student_discipline = list()
        for grade in self.data:
            if grade.student_id == student_id and grade.discipline_id == discipline_id:
                grades_student_discipline.append(grade.grade_value)
        return grades_student_discipline

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.data:
            repository_list_form.append(str(item))
        return repository_list_form

    def get_all_grades(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        repository_list_form = list()
        for item in self.data:
            repository_list_form.append(item)
        return repository_list_form

    def __len__(self):
        """
            This function returns the number of objects in the repository
            :return: an integer
        """
        return len(self.data)

    def __iter__(self):
        return iter(self.data)


# ================================================


class GradeBinFileRepository(GradeRepository):
    def __init__(self, grade_validator_class, file_name):
        super().__init__(grade_validator_class)
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        file = open(self._file_name, "rb")  # rb -> read, binary
        while True:
            try:
                self.data = pickle.load(file)
            except EOFError:
                break
        file.close()

    def _save_file(self):
        file = open(self._file_name, "wb")  # wb -> write, binary
        pickle.dump(self.data, file)
        file.close()

    def add_grade(self, grade):
        """
        1. Inherit all the functions and methods of the GradeRepository
        2. Save the grades to file
        """
        super(GradeBinFileRepository, self).add_grade(grade)
        self._save_file()
        if isinstance(grade, Grade) is False:
            raise GradeRepositoryError("Repository can only hold Grade instances")

    def remove_grade(self, grade_to_be_removed):
        super(GradeBinFileRepository, self).remove_grade(grade_to_be_removed)
        self._save_file()

    def __len__(self):
        return len(self.data)


# ==============================


class GradeTextFileRepository(GradeRepository):
    def __init__(self, grade_validator_class, file_name):
        super().__init__(grade_validator_class)
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        file = open(self._file_name, "rt")  # rt -> read, text-mode
        for line in file.readlines():
            _student_id, _discipline_id, value = line.split(maxsplit=2, sep=',')
            value = value.replace('\n', "")
            self.add_grade(Grade(_student_id, _discipline_id, int(value)))
        file.close()

    def _save_file(self):
        file = open(self._file_name, "wt")  # wt -> write, text-mode
        for grade in self.data:
            file.write(str(grade.student_id) + ',' + str(grade.discipline_id) + ',' + str(grade.grade_value) + "\n")
        file.close()

    def add_grade(self, entity):
        """
        1. Do whatever the add method in the base class does
        2. Save the ingredients to file
        """
        super(GradeTextFileRepository, self).add_grade(entity)
        self._save_file()

    def remove_grade(self, grade_to_be_removed):
        super(GradeTextFileRepository, self).remove_grade(grade_to_be_removed)
        self._save_file()
