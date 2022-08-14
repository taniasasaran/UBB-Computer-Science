class Grade:
    def __init__(self, discipline_id, student_id, grade_value):
        """
        This function creates a representation of a grade in form of a class
        :param discipline_id: string
        :param student_id: string
        :param grade_value: integer
        """
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__grade_value = grade_value

    @property
    def discipline_id(self):
        return str(self.__discipline_id)

    @property
    def student_id(self):
        return str(self.__student_id)

    @property
    def grade_value(self):
        return int(self.__grade_value)

    # @grade_value.setter
    # def grade_value(self, value):
    #     """
    #     This would have been useful if we could update the grade value
    #     :param value: an integer
    #     :return: None
    #     """
    #     self.__grade_value = value

    def __str__(self):
        """
                This function creates a string representation of a grade
                :return: a string
        """
        return f"Discipline_ID: {self.__discipline_id} Student_ID: {self.__student_id} GradeValue: {self.__grade_value}"