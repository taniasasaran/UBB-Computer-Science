import json
import pickle
from copy import deepcopy

from src.domain.discipline import Discipline
from src.domain.validators_and_errors import DisciplineRepositoryError
from src.repository.iterable_structure import Collection


class DisciplineCollection(Collection):
    def __init__(self):
        super().__init__()

    def __add__(self, item):
        super().__add__(item)

    def __iter__(self):
        return super().__iter__()

    def __delitem__(self, item_to_be_removed_id):
        new_list = list()
        for self._position in range(len(self.data)):
            if self.data[self._position].discipline_id != item_to_be_removed_id:
                new_list.append(self.data[self._position])
        self._data = deepcopy(new_list)

    def __set_name__(self, item_to_be_updated_id, new_name):
        for self._position in range(len(self._data)):
            if self._data[self._position].discipline_id == item_to_be_updated_id:
                self._data[self._position].name = new_name

    def __len__(self):
        return super().__len__()

    def __next__(self):
        return super().__next__()


class DisciplineRepository:
    def __init__(self, discipline_validator_class):
        self.data = Collection()
        self.__validator_class = discipline_validator_class

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
        for discipline in self.data:
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
        self.data.__add__(discipline)

    def remove_discipline(self, discipline_to_be_removed_id):
        """
        This function removes a discipline from the repository if the parameters are valid, otherwise it raises an error
        :param discipline_to_be_removed_id: a string
        :return:
        """
        if not self.discipline_id_existence(discipline_to_be_removed_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_removed_id} does not exist!")
        for i, discipline in enumerate(self.data):
            if discipline.discipline_id == discipline_to_be_removed_id:
                del self.data[i]
                break

    def update_discipline(self, discipline_to_be_updated_id, new_name):
        """
        This function changes the data from the repository
        :param discipline_to_be_updated_id: a string
        :param new_name: a string
        :return: none
        """
        if not self.discipline_id_existence(discipline_to_be_updated_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_updated_id} does not exist!")
        for discipline in range(len(self.data)):
            if self.data[discipline].discipline_id == discipline_to_be_updated_id:
                self.data[discipline].name = new_name

    def search_discipline_by_id(self, discipline_id):
        """
        This function gets all the disciplines which have the "discipline_id" contained in their discipline_id
        :param discipline_id: a string
        :return: a list of strings
        """
        list_matched_disciplines = list()
        for discipline in self.data:
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
        for discipline in self.data:
            if discipline_name.lower() in discipline.name.lower():
                list_matched_disciplines.append(str(discipline))
        return list_matched_disciplines

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.data:
            repository_list_form.append(str(item))
        return repository_list_form

    def get_all_disciplines(self):
        """
        This function returns the contents of the repository in form of a list of objects
        :return: a list of objects
        """
        repository_list_form = list()
        for item in self.data:
            repository_list_form.append(item)
        return repository_list_form

    def __len__(self):
        return self.data.__len__()


# =============================================


class DisciplineBinFileRepository(DisciplineRepository):
    def __init__(self, discipline_validator_class, file_name):
        super().__init__(discipline_validator_class)
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

    def add_discipline(self, discipline):
        """
        1. Inherit all the functions and methods of the DisciplineRepository
        2. Save the disciplines to file
        """
        if super(DisciplineBinFileRepository, self).discipline_id_existence(discipline.discipline_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline.discipline_id} already exists!")
        super(DisciplineBinFileRepository, self).add_discipline(discipline)
        self._save_file()

    def update_student(self, discipline_to_be_updated_id, new_name):
        if not super(DisciplineBinFileRepository, self).discipline_id_existence(discipline_to_be_updated_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_updated_id} does not exist!")
        super(DisciplineBinFileRepository, self).update_discipline(discipline_to_be_updated_id, new_name)
        self._save_file()

    def remove_student(self, discipline_to_be_removed_id):
        if not super(DisciplineBinFileRepository, self).discipline_id_existence(discipline_to_be_removed_id):
            raise DisciplineRepositoryError(f"Discipline with id={discipline_to_be_removed_id} does not exist!")
        super(DisciplineBinFileRepository, self).remove_discipline(discipline_to_be_removed_id)
        self._save_file()

    def __len__(self):
        return self.data.__len__()


# ===========================================


class DisciplineTextFileRepository(DisciplineRepository):
    def __init__(self, discipline_validator_class, file_name):
        super().__init__(discipline_validator_class)
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        file = open(self._file_name, "rt")  # rt -> read, text-mode
        for line in file.readlines():
            _discipline_id, name = line.split(maxsplit=1, sep=',')
            name = name.replace('\n', "")
            super(DisciplineTextFileRepository, self).add_discipline(Discipline(int(_discipline_id), name.strip("\n")))
        file.close()

    def _save_file(self):
        file = open(self._file_name, "wt")  # wt -> write, text-mode
        for discipline in self.data:
            file.write(str(discipline.discipline_id) + ',' + discipline.name + "\n")
        file.close()

    def add_discipline(self, discipline):
        """
        1. Do whatever the add method in the base class does
        2. Save the disciplines to file
        """
        super(DisciplineTextFileRepository, self).add_discipline(discipline)
        self._save_file()

    def update_student(self, discipline_to_be_updated_id, new_name):
        super(DisciplineTextFileRepository, self).update_discipline(discipline_to_be_updated_id, new_name)
        self._save_file()

    def remove_student(self, discipline_to_be_removed_id):
        super(DisciplineTextFileRepository, self).remove_discipline(discipline_to_be_removed_id)
        self._save_file()

    def __len__(self):
        return self.data.__len__()
