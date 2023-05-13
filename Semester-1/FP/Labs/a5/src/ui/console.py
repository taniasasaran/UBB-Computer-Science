from src.services.complex_service import ServiceError


def empty_list():
    """
    This function creates an empty list.
    :return: an empty list
    """
    return lambda: []


class Console:
    def __init__(self, complex_service):
        """
        This function is the constructor of the complex_service in the console Class.
        It associates functions to each command via a dictionary
        :param complex_service: a Class
        """
        self.__complex_service = complex_service
        self.__commands = {
            "1": (self.__complex_service.add_complex_number, lambda: [input("")]),
            "2": (self.__complex_service.get_complex_numbers_as_string, empty_list()),
            "3": (self.__complex_service.filter_list_of_complex_numbers, lambda: Console.__get_filter_parameters(input(""))),
            "4": (self.__complex_service.undo, empty_list())
        }

    def __print_menu(self):
        command_sentences = ["1 to add a complex number", "2 to display the list of numbers", "3 to filter the list ; please introduce the start and the end index separated by space", "4 to undo the last operation that modified data"]
        print(*(command for command in command_sentences), "exit", sep="\n")
        print("    Command: ")

    def start(self):
        while True:
            self.__print_menu()
            command = input()
            command = command.strip()
            if command == "exit":
                break

            try:
                parameters = self.__commands[command][1]()
                return_value = self.__commands[command][0](*parameters)
                if return_value is not None:
                    print(return_value)
            except KeyError:
                print(f"command {command} not found.")
            except ValueError as ve:
                print(ve)
            except ServiceError as se:
                print(se)

    @staticmethod
    def __get_filter_parameters(parameters_string):
        """
        This function gets the parameters for the filter_list_of_complex_numbers function
        :param parameters_string: a string containing two numerical values
        :return: the start and end (integer) parameters for the function, otherwise it raises errors
        """
        parameters_string = parameters_string.strip()
        try:
            left_string, right_string = parameters_string.split(" ")
        except ValueError as ve:
            raise ValueError("Range should be specified as: \"left right\".", ve)

        try:
            start = int(left_string)
            end = int(right_string)
        except ValueError as ve:
            raise ValueError("Start and end indexes must be integers.", ve)
        return start, end

