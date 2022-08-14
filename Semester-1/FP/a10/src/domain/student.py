class Student:
    def __init__(self, student_id, name):
        """
        This function creates a representation of a student in form of a class
        :param student_id: string
        :param name: string
        """
        self.__student_id = student_id
        self.__name = name

    @property
    def student_id(self):
        return str(self.__student_id)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    def __str__(self):
        """
                This function creates a string representation of a student
                :return: a string
        """
        return f"ID: {self.__student_id} NAME: {self.__name}"
