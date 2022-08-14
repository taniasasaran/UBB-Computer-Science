from src.domain.discipline import Discipline


class DisciplineService:
    def __init__(self, repository):
        self.__discipline_repository = repository

    def add_discipline(self, discipline_id, name):
        """
        This function creates an object with the parameters received and calls another function to add the discipline
        :param discipline_id: string
        :param name: string
        :return: none
        """
        discipline = Discipline(discipline_id, name)
        self.__discipline_repository.add_discipline(discipline)

    def remove_discipline(self, discipline_id):
        """
        This function calls a function from the repository to remove the discipline with the id specified
        and also the grades assigned in that discipline
        :param discipline_id: string
        :return:none
        """
        self.__discipline_repository.remove_discipline(discipline_id)

    def update_discipline(self, discipline_id, new_name):
        """
        This function calls a function from the repository to update the name of a discipline with the id specified
        :param discipline_id: string
        :param new_name: string
        :return: none
        """
        self.__discipline_repository.update_discipline(discipline_id, new_name)

    def search_discipline_by_id(self, discipline_id):
        """
        This function calls a function from the repository to search disciplines by id
        :param discipline_id: string
        :return: list of disciplines which have discipline_id part of their id
        """
        return self.__discipline_repository.search_discipline_by_id(discipline_id)

    def search_discipline_by_name(self, discipline_name):
        """
        This function calls a function from the repository to search disciplines by name
        :param discipline_name: string
        :return: list of disciplines which have discipline_name part of their name
        """
        return self.__discipline_repository.search_discipline_by_name(discipline_name)

    def get_all_str(self):
        """
            This function returns the contents of the repository in form of a list of strings
            :return: a list of strings
        """
        return self.__discipline_repository.get_all_str()

    def get_all_disciplines(self):
        """
            This function returns the contents of the repository in form of a list of objects
            :return: a list of objects
        """
        return self.__discipline_repository.get_all_disciplines()

    def __iter__(self):
        return iter(self.__discipline_repository)
