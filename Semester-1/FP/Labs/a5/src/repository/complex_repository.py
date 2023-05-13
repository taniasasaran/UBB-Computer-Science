from src.domain.complex import Complex


class ComplexRepository:
    def __init__(self):
        self.__numbers = []

    @classmethod
    def add_10_complex_numbers_in_repository(cls):
        """
        This function adds 10 complex numbers in the repository
        :return: a list with 10 elements
        """
        repository = ComplexRepository()
        from src.domain.complex import Complex
        for i in range(1, 11):
            repository.add_number(Complex(i, i+10))
        return repository

    def __len__(self):
        return len(self.__numbers)

    def add_number(self, complex_number: Complex):
        """
        This function adds a number to the repository.
        :param complex_number: complex number to be added
        :return: None
        """
        self.__numbers.append(complex_number)

    def get_numbers_as_string(self):
        """
        This function creates a list of all the numbers currently in the repository in string form.
        :return: a list of strings
        """
        repository_string_form = ""
        for complex_number in self.__numbers:
            repository_string_form += str(complex_number)
            repository_string_form += '\n'
        return repository_string_form

    def filter(self, start: int, end: int):
        """
        This function modifies the repository to have only the items between start and end.
        :param start: left border of the interval, integer
        :param end: right border of the interval, integer
        :return: None
        """
        if start < 0 or end >= len(self.__numbers) or start > end:
            raise ValueError(
                f"invalid range. "
                f"start and end should be between 0 and {len(self.__numbers) - 1}."
            )
        self.__numbers = [self.__numbers[i] for i in range(len(self.__numbers)) if i in range(start, end+1)]

    @property
    def numbers(self):
        return self.__numbers


def test_add_10_complex_numbers_in_repository__length_10__true():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    assert len(repository) == 10


def test_add_number__last_number__and__length_1__true():
    repository = ComplexRepository()
    repository.add_number(Complex(24, 5))
    assert len(repository) == 1
    assert repository.numbers[-1] == Complex(24, 5)


def test_add_number__last_number__and__length_11__true():
    repository = ComplexRepository.add_10_complex_numbers_in_repository()
    repository.add_number(Complex(25, -4))
    assert len(repository) == 11
    assert repository.numbers[-1] == Complex(25, -4)


if __name__ == '__main__':
    test_add_10_complex_numbers_in_repository__length_10__true()
    test_add_number__last_number__and__length_1__true()
    test_add_number__last_number__and__length_11__true()
