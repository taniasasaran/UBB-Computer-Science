from copy import deepcopy


class GradeRepository:
    def __init__(self, grade_validator_class):
        self.__validator_class = grade_validator_class
        self.__data = list()

    def add_grade(self, grade):
        """
            This function adds a grade in the repository
            :param grade: an object(class)
            :return: none
        """
        self.__validator_class.validate(grade)
        self.__data.append(grade)

    def remove_grade(self, grade_to_be_removed):
        """
        This function removes the grade
        :param grade_to_be_removed: an object(class)
        :return: None
        """
        for i, grade in reversed(list(enumerate(self.__data))):
            if grade.student_id == grade_to_be_removed.student_id and \
                    grade.discipline_id == grade_to_be_removed.discipline_id:
                del self.__data[i]
                break

    def remove_grades_discipline(self, discipline_id):
        """
            This function removes all the grades of a discipline from the repository if the parameters are valid,
            otherwise it raises an error.
            This function will be called from remove_discipline
            :param discipline_id: a string
            :return: none
        """
        updated_list = []
        i = 0
        for grade in self.__data:
            if grade.discipline_id != discipline_id:
                updated_list.append(self.__data[i])
            i += 1
        self.__data = deepcopy(updated_list)

    def remove_grades_student(self, student_id):
        """
            This function removes all the grades of a student from the repository if the parameters are valid,
            otherwise it raises an error.
            This function will be called from remove_student
            :param student_id: a string
            :return: none
        """
        updated_list = []
        i = 0
        for grade in self.__data:
            if grade.student_id != student_id:
                updated_list.append(self.__data[i])
            i += 1
        self.__data = deepcopy(updated_list)

    def get_grades_student_discipline(self, student_id, discipline_id):
        """
        This function creates a list of all the grades of a student at a certain discipline
        :param student_id: string
        :param discipline_id: string
        :return: list of integers
        """
        grades_student_discipline = list()
        for grade in self.__data:
            if grade.student_id == student_id and grade.discipline_id == discipline_id:
                grades_student_discipline.append(grade.grade_value)
        return grades_student_discipline

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.__data:
            repository_list_form.append(str(item))
        return repository_list_form

    def get_all_grades(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        repository_list_form = list()
        for item in self.__data:
            repository_list_form.append(item)
        return repository_list_form

    def __len__(self):
        """
            This function returns the number of objects in the repository
            :return: an integer
        """
        return len(self.__data)

    def __iter__(self):
        return iter(self.__data)
