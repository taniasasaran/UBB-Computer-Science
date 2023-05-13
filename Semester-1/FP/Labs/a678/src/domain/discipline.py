class Discipline:
    def __init__(self, discipline_id, name):
        """
        This function creates a representation of a discipline in form of a class
        :param discipline_id: string
        :param name: string
        """
        self.__discipline_id = discipline_id
        self.__name = name

    @property
    def discipline_id(self):
        return str(self.__discipline_id)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    def __str__(self):
        """
        This function creates a string representation of a discipline
        :return: a string
        """
        return f"ID: {self.__discipline_id} NAME: {self.__name}"
