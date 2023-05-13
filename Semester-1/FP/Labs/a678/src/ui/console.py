from src.domain.validators_and_errors import StudentsRegisterManagementException, ConsoleException
# from src.services.undoredo import undoAction
from src.services.undo_redo_service import UndoRedoManager


def empty_list():
    """
    This function creates an empty list.
    :return: an empty list
    """
    return lambda: []


class Console1:
    def __init__(self, student_service, discipline_service, grade_service):
        """
        This function is the constructor of the UI in the console Class.
        It associates functions from the corresponding services to each command via ifs
        :param student_service: a Class
        :param discipline_service: a Class
        :param grade_service: a Class
        """
        self.__statistics = ["failing", "best_students", "sort_disciplines"]
        self.__student_service = student_service
        self.__discipline_service = discipline_service
        self.__grade_service = grade_service
        self.__commands = ["add", "remove", "update", "list", "search", "failing", "best_students", "sort_disciplines"]

    def __print_menu(self):
        print(*(command for command in self.__commands), "exit", sep="\n")
        print("    Command: ")

    def call_statistics_functions(self, command):
        if command == "failing":
            repository_string_form = ""
            for item in self.__grade_service.list_failing_students():
                repository_string_form += str(item)
                repository_string_form += '\n'
            print(repository_string_form)
        if command == "best_students":
            repository_string_form = ""
            for item in self.__grade_service.list_students_descending_averages():
                repository_string_form += str(item[1])   # without 1 to show also their aggregated average
                repository_string_form += '\n'
            print(repository_string_form)
        if command == "sort_disciplines":
            repository_string_form = ""
            for item in self.__grade_service.list_disciplines_descending_averages():
                repository_string_form += str(item)   # without 1 to show their aggregated average
                repository_string_form += '\n'
            print(repository_string_form)

    def call_student_functions(self, command):
        if command == "search":
            parameters = input("Please introduce the id or name: ").strip()
            list_matched_students = ""
            if parameters.isnumeric():
                for item in self.__student_service.search_student_by_id(parameters):
                    list_matched_students += str(item)
                    list_matched_students += '\n'
            else:
                for item in self.__student_service.search_student_by_name(parameters):
                    list_matched_students += str(item)
                    list_matched_students += '\n'
            if list_matched_students == "":
                print("There are no students with that ID or name!")
            else:
                print(list_matched_students)
        if command == "add":
            parameters = input("Please introduce the id and name: ").strip()
            parameters = self.get_2_parameters(parameters)
            self.__student_service.add_student(*parameters)
        elif command == "update":
            parameters = input("Please introduce the id and the new name: ").strip()
            parameters = self.get_2_parameters(parameters)
            self.__student_service.update_student(*parameters)
        elif command == "remove":
            parameter = input("Please introduce the id: ").strip()
            self.__student_service.remove_student(parameter)
        elif command == "list":
            repository_string_form = ""
            for item in self.__student_service.get_all_str():
                repository_string_form += str(item)
                repository_string_form += '\n'
            print(repository_string_form)

    def call_discipline_functions(self, command):
        if command == "search":
            parameters = input("Please introduce the id or name: ").strip()
            list_matched_disciplines = ""
            if parameters.isnumeric():
                for item in self.__discipline_service.search_discipline_by_id(parameters):
                    list_matched_disciplines += str(item)
                    list_matched_disciplines += '\n'
            else:
                for item in self.__discipline_service.search_discipline_by_name(parameters):
                    list_matched_disciplines += str(item)
                    list_matched_disciplines += '\n'
            if list_matched_disciplines=="":
                print("There are no disciplines with that ID or name!")
            else:
                print(list_matched_disciplines)
        if command == "add":
            parameters = input("Please introduce the id and name: ").strip()
            parameters = self.get_2_parameters(parameters)
            self.__discipline_service.add_discipline(*parameters)
        elif command == "update":
            parameters = input("Please introduce the id and the new name: ").strip()
            parameters = self.get_2_parameters(parameters)
            self.__discipline_service.update_discipline(*parameters)
        elif command == "remove":
            parameter = input("Please introduce the id: ").strip()
            self.__discipline_service.remove_discipline(parameter)
        elif command == "list":
            repository_string_form = ""
            for item in self.__discipline_service.get_all_str():
                repository_string_form += str(item)
                repository_string_form += '\n'
            print(repository_string_form)

    def call_grade_functions(self, command):
        if command == "add":
            parameters = input("Please introduce the discipline_id, the student_id and the grade: ").strip()
            parameters = self.get_3_parameters(parameters)
            self.__grade_service.add_grade(*parameters)
        elif command == "list":
            repository_string_form = ""
            for item in self.__grade_service.get_all_str():
                repository_string_form += str(item)
                repository_string_form += '\n'
            print(repository_string_form)
        else:
            raise KeyError(f"You cannot {command} a grade!")

    def start(self):
        while True:
            self.__print_menu()
            command = input()
            command = command.strip()
            if command == "exit":
                break
            try:
                if command not in self.__commands:
                    raise KeyError(f"The command {command} was not implemented!")
                if command in self.__statistics:
                    self.call_statistics_functions(command)
                else:
                    student_discipline_grade = input(f"What do you want to {command}? ").strip()
                    if student_discipline_grade == "student":
                        self.call_student_functions(command)
                    elif student_discipline_grade == "discipline":
                        self.call_discipline_functions(command)
                    elif student_discipline_grade == "grade":
                        self.call_grade_functions(command)
                    else:
                        raise StudentsRegisterManagementException(f"Please write 'student', 'discipline' or 'grade'!")
            except KeyError as ke:
                print(ke)
            except StudentsRegisterManagementException as srme:
                print(srme)

    @staticmethod
    def get_2_parameters(parameters_string):
        parameters_string = parameters_string.strip()
        try:
            first_parameter, second_parameter = parameters_string.split(maxsplit=1)
            first_parameter = first_parameter.strip()
            second_parameter = second_parameter.strip()
        except ValueError as ve:
            raise ConsoleException("Please introduce exactly 2 parameters separated by space", ve)
        return str(first_parameter), str(second_parameter)

    @staticmethod
    def get_3_parameters(parameters_string):
        parameters_string = parameters_string.strip()
        try:
            first_parameter, second_string = parameters_string.split(maxsplit=1)
            first_parameter = first_parameter.strip()
            second_string = second_string.strip()
            second_parameter, third_parameter = second_string.split(maxsplit=1)
            second_parameter = second_parameter.strip()
            third_parameter = third_parameter.strip()
        except ValueError as ve:
            raise ConsoleException("Please introduce exactly 3 parameters separated by space", ve)
        return str(first_parameter), str(second_parameter), str(third_parameter)


class Console2:
    def __init__(self, student_service, discipline_service, grade_service):
        self.__student_service = student_service
        self.__discipline_service = discipline_service
        self.__grade_service = grade_service
        self.__undoable_commands = ['1', '2', '3', '5', '6', '7', '9']
        # self.__undo_redo = undoAction(self.__student_service, self.__discipline_service, self.__grade_service)
        self.__undo_redo = UndoRedoManager(discipline_service, student_service, grade_service)
        self.__commands = {
            "1": (self.__student_service.add_student, lambda: Console2.get_2_parameters(input("Please introduce the id and name: "))),
            "2": (self.__student_service.remove_student, lambda: [input("Please introduce the id: ").strip()]),
            "3": (self.__student_service.update_student, lambda: Console2.get_2_parameters(input("Please introduce the id and the new name: "))),
            "4": (self.__student_service.get_all_str, empty_list()),
            "5": (self.__discipline_service.add_discipline, lambda: Console2.get_2_parameters(input("Please introduce the id and name: "))),
            "6": (self.__discipline_service.remove_discipline, lambda: [input("Please introduce the id: ").strip()]),
            "7": (self.__discipline_service.update_discipline, lambda: Console2.get_2_parameters(input("Please introduce the id and the new name: "))),
            "8": (self.__discipline_service.get_all_str, empty_list()),
            "9": (self.__grade_service.add_grade, lambda: Console2.get_3_parameters(input("Please introduce the discipline_id, the student_id and the grade: "))),
            "10":(self.__grade_service.get_all_str, empty_list()),
            "11":(self.__student_service.search_student_by_id, lambda: [input("Please introduce the id: ").strip()]),
            "12":(self.__student_service.search_student_by_name, lambda: [input("Please introduce the name: ").strip()]),
            "13":(self.__discipline_service.search_discipline_by_id, lambda: [input("Please introduce the id: ").strip()]),
            "14":(self.__discipline_service.search_discipline_by_name, lambda: [input("Please introduce the name: ").strip()]),
            "15":(self.__grade_service.list_failing_students, empty_list()),
            "16":(self.__grade_service.list_students_descending_averages, empty_list()),
            "17":(self.__grade_service.list_disciplines_descending_averages, empty_list()),
        }

    @staticmethod
    def __print_menu():
        command_sentences = ["1 to add a student", "2 to remove a student", "3 to update a student",
                             "4 to list all students", "5 to add a discipline", "6 to remove a discipline",
                             "7 to update a discipline", "8 to list all disciplines", "9 to add a grade",
                             "10 to list all grades", "11 to search a student by id", "12 to search a student by name",
                             "13 to search a discipline by id", "14 to search a discipline by name",
                             "15 to display all failing students", "16 to display best students",
                             "17 to display disciplines sorted by average",
                             "undo to undo the last performed operation - does not work yet",
                             "redo to redo the last performed operation - does not work yet"]
        print(*(command for command in command_sentences), "exit", sep="\n")
        print("    Command: ")


    def start(self):
        while True:
            self.__print_menu()
            command = input()
            command = command.strip()
            if command == "exit":
                break

            # if command == "undo":
            #     self.__undo_redo.undoController()
            #
            # if command == "redo":
            #     self.__undo_redo.redoController()

            try:
                parameters = self.__commands[command][1]()
                # if command in self.__undoable_commands:
                #     self.__undo_redo.register_operation(..., handler, parameters)

                #     self.__undo_redo.addToUndoList(command, parameters)
                #     self.__undo_redo.addToRedoList(command, parameters)
                return_value = self.__commands[command][0](*parameters)
                if return_value is not None:
                    repository_string_form = ""
                    for item in return_value:
                        repository_string_form += str(item)
                        repository_string_form += '\n'
                    print(repository_string_form)
            except KeyError:
                print(f"command {command} not found.")
            except StudentsRegisterManagementException as srme:
                print(srme)

    @staticmethod
    def get_2_parameters(parameters_string):
        parameters_string = parameters_string.strip()
        try:
            first_parameter, second_parameter = parameters_string.split(maxsplit=1)
            first_parameter = first_parameter.strip()
            second_parameter = second_parameter.strip()
        except ValueError as ve:
            raise ConsoleException("Please introduce exactly 2 parameters separated by space", ve)
        return [str(first_parameter), str(second_parameter)]

    @staticmethod
    def get_3_parameters(parameters_string):
        parameters_string = parameters_string.strip()
        try:
            first_parameter, second_string = parameters_string.split(maxsplit=1)
            first_parameter = first_parameter.strip()
            second_string = second_string.strip()
            second_parameter, third_parameter = second_string.split(maxsplit=1)
            second_parameter = second_parameter.strip()
            third_parameter = third_parameter.strip()
        except ValueError as ve:
            raise ConsoleException("Please introduce exactly 3 parameters separated by space", ve)
        return [str(first_parameter), str(second_parameter), str(third_parameter)]

