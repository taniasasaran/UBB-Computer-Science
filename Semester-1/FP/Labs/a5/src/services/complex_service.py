from copy import deepcopy
from typing import List

from src.domain.complex import Complex
from src.repository.complex_repository import ComplexRepository


class ServiceError(Exception):
    """
    This function creates a new type of exception.
    :return: None
    """
    pass


class ComplexService:
    def __init__(self, repository: ComplexRepository):
        self.__history = [repository]

    def add_complex_number(self, number: str):
        """
        Creates a new version of the repository with a new number added at the end.
        :param number: complex number to be added represented as a string
        :return: None
        """
        self.__history.append(deepcopy(self.__history[-1]))
        self.__history[-1].add_number(Complex.transform_complex_number_string_to_class(number))

    def get_complex_numbers_as_string(self) -> List[str]:
        """
        Returns a list of all the complex numbers currently in the repository in string format.
        :return: a list of strings
        """
        return self.__history[-1].get_numbers_as_string()

    def filter_list_of_complex_numbers(self, start: str, end: str):
        """
        Creates a new version of the repository containing only the items between
        start and end.
        :param start: left border of the interval, string
        :param end: right border of the interval, string
        :return: None
        """
        self.__history.append(deepcopy(self.__history[-1]))
        self.__history[-1].filter(int(start), int(end))

    def undo(self):
        """
        This function undoes last operation that modified repository to the previous version.
        This step can be repeated.
        :return: None
        """
        if len(self.__history) == 1:
            raise ServiceError("no operations left to undo")
        self.__history.pop()

    @property
    def numbers(self):
        return self.__history[-1].numbers


def test_service_add_complex_number__valid_string__no_errors():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    service = ComplexService(repository)
    service.add_complex_number("  24 +   5i ")
    assert service.numbers[-1] == Complex(24, 5)

def test_service_add_complex_number__i__no_errors():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    service = ComplexService(repository)
    service.add_complex_number("i")
    assert service.numbers[-1] == Complex(0, 1)

def test_service_add_complex_number__negative_i__noerrors():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    service = ComplexService(repository)
    service.add_complex_number("-i")
    assert service.numbers[-1] == Complex(0, -1)

def test_service_add_complex_number__invalid_string__errors():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    service = ComplexService(repository)
    try:
        service.add_complex_number("iii")
        assert False
    except ValueError:
        assert True


if __name__ == '__main__':
    test_service_add_complex_number__valid_string__no_errors()
    test_service_add_complex_number__i__no_errors()
    test_service_add_complex_number__negative_i__noerrors()
    test_service_add_complex_number__invalid_string__errors()