from src.domain.student import Student


class StudentService:
    def __init__(self, student_repository):
        self.__student_repository = student_repository

    def add_student(self, student_id, name):
        """
        This function creates an object with the parameters received and calls another function to add the student
        :param student_id: string
        :param name: string
        :return: none
        """
        student = Student(student_id, name)
        self.__student_repository.add_student(student)

    def add_20_students_in_repository(self):
        """
            This function adds 20 students in the repository
            :return: none
        """
        list_of_names = ["Liam", "Olivia", "Noah", "Emma", "Oliver", "Ava", "Elijah", "Charlotte", "William", "Sophia",
                         "James", "Amelia", "Benjamin", "Isabella", "Lucas", "Mia", "Henry", "Evelyn", "Alexander",
                         "Harper"]
        i = 0
        for name in list_of_names:
            self.add_student(str(i+1), name)
            i = i + 1

    def remove_student(self, student_id):
        """
        This function calls a function from the repository to remove the student with the id specified
        and also the student assigned to that discipline
        :param student_id: string
        :return:
        """
        self.__student_repository.remove_student(student_id)

    def update_student(self, student_id, new_name):
        """
        This function calls a function from the repository to update the name of a student with the id specified
        :param student_id: string
        :param new_name: string
        :return:
        """
        self.__student_repository.update_student(student_id, new_name)

    def search_student_by_id(self, student_id):
        """
        This function calls a function from the repository to search students by id
        :param student_id: string
        :return: list of disciplines which have student_id part of their id
        """
        return self.__student_repository.search_student_by_id(student_id)

    def find_student_by_id(self, student_id):
        """
            This function calls a function from the repository to get the student's attributes based on its student_id
        :param student_id: a string
        :return: a list consisting of student.student_id and student.name
        """
        return self.__student_repository.find_student_by_id(student_id)

    def search_student_by_name(self, student_name):
        """
        This function calls a function from the repository to search students by name
        :param student_name: string
        :return: list of students which have student_name part of their name
        """
        return self.__student_repository.search_student_by_name(student_name)

    def get_all_str(self):
        """
            This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        return self.__student_repository.get_all_str()

    def get_all_students(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        return self.__student_repository.get_all_students()

    def __iter__(self):
        return iter(self.__student_repository)
