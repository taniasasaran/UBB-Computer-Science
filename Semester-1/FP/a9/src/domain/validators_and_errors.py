class StudentsRegisterManagementException(Exception):
    pass


class UndoError(StudentsRegisterManagementException):
    pass


class ConsoleException(StudentsRegisterManagementException):
    pass


class StudentRepositoryError(StudentsRegisterManagementException):
    pass


class DisciplineRepositoryError(StudentsRegisterManagementException):
    pass


class GradeRepositoryError(StudentsRegisterManagementException):
    pass


class StudentValidatorException(StudentsRegisterManagementException):
    pass


class DisciplineValidatorException(StudentsRegisterManagementException):
    pass


class GradeValidatorException(StudentsRegisterManagementException):
    pass


class StudentValidator:
    @staticmethod
    def validate(student):
        """
        This function checks if the student_id is an integer >0 and the name an alphabetical string
        :param student: an object(class)
        :return: errors or none
        """
        if not str(student.student_id).isnumeric() or int(student.student_id) < 1:
            raise StudentValidatorException("The id should be a positive integer, greater than 0!")
        # if not student.name.isalpha():
        #     raise StudentValidatorException("The name should have only letters!")


class DisciplineValidator:
    @staticmethod
    def validate(discipline):
        """
        This function checks if the discipline_id is an integer >0 and the name an alphabetical string
        :param discipline: an object(class)
        :return: errors or none
        """
        if not str(discipline.discipline_id).isnumeric() or int(discipline.discipline_id) < 1:
            raise DisciplineValidatorException("The id should be a positive integer, greater than 0!")
        # if not discipline.name.isalpha():
        #     raise DisciplineValidatorException("The name should have only letters!")


class GradeValidator:
    @staticmethod
    def validate(grade):
        """
        This function checks if the discipline_id is an integer >0, the student_id is an integer >0
        and the grade is between 1 and 10
        :param grade:  an object(class)
        :return: errors or none
        """
        if not (str(grade.grade_value).isnumeric() and 1 <= int(grade.grade_value) <= 10):
            raise GradeValidatorException("The grade should be an integer between 1 and 10!")
        if str(grade.student_id).isnumeric() and int(grade.student_id) < 1:
            raise StudentValidatorException("The student id should be a positive integer, greater than 0!")
        if str(grade.discipline_id).isnumeric() and int(grade.discipline_id) < 1:
            raise DisciplineValidatorException("The discipline id should be a positive integer, greater than 0!")
