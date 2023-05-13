from src.repository.complex_repository import ComplexRepository
from src.services.complex_service import ComplexService
from src.ui.console import Console


def main():
    """
    This is the main function of the program.
    :return: None
    """
    complex_repository = ComplexRepository.add_10_complex_numbers_in_repository()
    complex_service = ComplexService(complex_repository)
    console = Console(complex_service)

    console.start()


if __name__ == '__main__':
    main()