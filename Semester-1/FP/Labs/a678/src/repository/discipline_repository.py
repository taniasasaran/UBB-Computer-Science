from src.domain.discipline import Discipline
from src.domain.validators_and_errors import DisciplineRepositoryError


class DisciplineRepository:
    def __init__(self, discipline_validator_class):
        self.__validator_class = discipline_validator_class
        self.__data = list()

    def add_5_disciplines_in_repository(self):
        """
        This function adds 5 disciplines in the repository
        :return: none
        """
        list_of_discipline_names = ["Algebra", "ASC", "Calculus", "CL", "FP"]
        i = 0
        for discipline_name in list_of_discipline_names:
            discipline = Discipline(str(i + 1), discipline_name)
            i = i + 1
            self.add_discipline(discipline)

    def discipline_id_existence(self, id_to_be_checked):
        """
            This function checks if a discipline with a specified ID is in repository or not
            :param id_to_be_checked: a string
            :return: True or False
        """
        for discipline in self.__data:
            if discipline.discipline_id == id_to_be_checked:
                return True
        return False

    def add_discipline(self, discipline):
        """
        This function adds a new discipline in the repository if the parameters are valid, otherwise it raises an error
        :param discipline: an object(class)
        :return: none
        """
        self.__validator_class.validate(discipline)
        if self.discipline_id_existence(discipline.discipline_id):
            raise DisciplineRepositoryError(f"Discipline with ID={discipline.discipline_id} already exists!")
        self.__data.append(discipline)

    def remove_discipline(self, discipline_to_be_removed_id):
        """
        This function removes a discipline from the repository if the parameters are valid, otherwise it raises an error
        :param discipline_to_be_removed_id: a string
        :return:
        """
        if not self.discipline_id_existence(discipline_to_be_removed_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_removed_id} does not exist!")
        for i, discipline in enumerate(self.__data):
            if discipline.discipline_id == discipline_to_be_removed_id:
                del self.__data[i]

    def update_discipline(self, discipline_to_be_updated_id, new_name):
        """
        This function changes the data from the repository
        :param discipline_to_be_updated_id: a string
        :param new_name: a string
        :return: none
        """
        if not self.discipline_id_existence(discipline_to_be_updated_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_updated_id} does not exist!")
        for i, discipline in enumerate(self.__data):
            if discipline.discipline_id == discipline_to_be_updated_id:
                discipline.name = new_name

    def search_discipline_by_id(self, discipline_id):
        """
        This function gets all the disciplines which have the "discipline_id" contained in their discipline_id
        :param discipline_id: a string
        :return: a list of strings
        """
        list_matched_disciplines = list()
        for discipline in self.__data:
            if discipline_id in discipline.discipline_id:
                list_matched_disciplines.append(str(discipline))
        return list_matched_disciplines

    def search_discipline_by_name(self, discipline_name):
        """
            This function gets all the disciplines which have the "discipline_name" contained in their name
            :param discipline_name: a string
            :return: a list of strings
        """
        list_matched_disciplines = list()
        for discipline in self.__data:
            if discipline_name.lower() in discipline.name.lower():
                list_matched_disciplines.append(str(discipline))
        return list_matched_disciplines

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.__data:
            repository_list_form.append(str(item))
        return repository_list_form

    def get_all_disciplines(self):
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
