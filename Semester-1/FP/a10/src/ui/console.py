from src.domain.discipline import Discipline
from src.domain.student import Student
from src.domain.validators_and_errors import StudentsRegisterManagementException, UndoError


class Console:
    def __init__(self, student_service, discipline_service, grade_service, undo_redo_service):
        self.__student_service = student_service
        self.__discipline_service = discipline_service
        self.__grade_service = grade_service
        self.__undo_redo_service = undo_redo_service
        self.__commands = {
            "1": self.__ui_add_student,
            "2": self.__ui_remove_student,
            "3": self.__ui_update_student_name,
            "4": self.__ui_print_students,
            "5": self.__ui_add_discipline,
            "6": self.__ui_remove_discipline,
            "7": self.__ui_update_discipline_name,
            "8": self.__ui_print_disciplines,
            "9": self.__ui_add_grade,
            "10": self.__ui_print_list_of_grades,
            "11": self.__ui_search_student_by_id,
            "12": self.__ui_search_student_by_name,
            "13": self.__ui_search_discipline_by_id,
            "14": self.__ui_search_discipline_by_name,
            "15": self.__ui_print_failing_students,
            "16": self.__ui_print_students_best_school_situation,
            "17": self.__ui_print_disciplines_descending_averages,
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
                             "UNDO to undo the last performed operation",
                             "REDO to redo the last performed operation",
                             "MENU to print the menu"]
        print(*(command for command in command_sentences), "EXIT", sep="\n")
        print("    Command: ")

    def __ui_add_student(self):  # undoed
        try:
            student_id = int(input("Please introduce the student_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        student_id = str(student_id)
        name = input("Please introduce the name: ").strip()
        self.__student_service.add_student(student_id, name)
        self.__undo_redo_service.add_command_to_stack("sAdd", Student(student_id, name))
        print("Student successfully added")

    def __ui_remove_student(self):  # undoed
        try:
            student_id = int(input("Please introduce the student_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        student_id = str(student_id)
        all_students = self.__student_service.get_all_students()
        all_grades = self.__grade_service.get_all_grades()

        student_id_has_grades = False
        for grade in all_grades:
            if grade.student_id == student_id:
                student_id_has_grades = True
        operations_list = list()
        if student_id_has_grades:
            for student in all_students:
                if student.student_id == student_id:
                    for grade in all_grades:
                        if grade.student_id == student_id:
                            self.__grade_service.remove_grade(grade.discipline_id, grade.student_id)
                            operations_list.append(
                                ["delete", [grade.discipline_id, grade.student_id, grade.grade_value]])
                    self.__student_service.remove_student(student_id)
                    operations_list.append(["sRemove", Student(student_id, student.name)])
                    self.__undo_redo_service.add_command_to_stack("cascade", operations_list)
        else:
            for student in all_students:
                if student.student_id == student_id:
                    self.__student_service.remove_student(student_id)
                    operations_list.append(["sRemove", Student(student_id, student.name)])
                    self.__undo_redo_service.add_command_to_stack("cascade", operations_list)

    def __ui_update_student_name(self):  # undoed
        try:
            student_id = int(input("Please introduce the student_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        student_id = str(student_id)
        new_name = input("Please introduce the new name: ").strip()
        all_students = self.__student_service.get_all_students()
        for student in all_students:
            if student.student_id == student_id:
                self.__undo_redo_service.add_command_to_stack("sUpdate", [student_id, student.name, new_name])
        self.__student_service.update_student(student_id, new_name)

    def __ui_print_students(self):  # we dont have to undo
        all_students = self.__student_service.get_all_students()
        if all_students is not None:
            repository_string_form = ""
            for student in all_students:
                repository_string_form += str(student)
                repository_string_form += '\n'
            print(repository_string_form)

    #   Here comes the discipline part
    def __ui_add_discipline(self):  # undoed
        try:
            discipline_id = int(input("Please introduce the discipline_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        discipline_id = str(discipline_id)
        name = input("Please introduce the name: ").strip()
        self.__discipline_service.add_discipline(discipline_id, name)
        self.__undo_redo_service.add_command_to_stack("dAdd", Discipline(discipline_id, name))
        print("Discipline successfully added")

    def __ui_remove_discipline(self):  # undoed
        try:
            discipline_id = int(input("Please introduce the discipline_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        discipline_id = str(discipline_id)
        all_disciplines = self.__discipline_service.get_all_disciplines()
        all_grades = self.__grade_service.get_all_grades()
        discipline_id_has_grades = False
        for grade in all_grades:
            if grade.discipline_id == discipline_id:
                discipline_id_has_grades = True
        operations_list = list()
        if discipline_id_has_grades:
            for discipline in all_disciplines:
                if discipline.discipline_id == discipline_id:
                    for grade in all_grades:
                        if grade.discipline_id == discipline_id:
                            self.__grade_service.remove_grade(discipline_id, grade.student_id)
                            operations_list.append(["delete", [discipline_id, grade.student_id, grade.grade_value]])
                    self.__discipline_service.remove_discipline(discipline_id)
                    operations_list.append(["dRemove", Discipline(discipline_id, discipline.name)])
                    self.__undo_redo_service.add_command_to_stack("cascade", operations_list)
        else:
            for discipline in all_disciplines:
                if discipline.discipline_id == discipline_id:
                    self.__discipline_service.remove_discipline(discipline_id)
                    operations_list.append(["dRemove", Discipline(discipline_id, discipline.name)])
                    self.__undo_redo_service.add_command_to_stack("cascade", operations_list)

    def __ui_update_discipline_name(self):  # undoed
        try:
            discipline_id = int(input("Please introduce the discipline_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        discipline_id = str(discipline_id)
        new_name = input("Please introduce the new name: ").strip()
        all_disciplines = self.__discipline_service.get_all_disciplines()
        for discipline in all_disciplines:
            if discipline.discipline_id == discipline_id:
                self.__undo_redo_service.add_command_to_stack("dUpdate", [discipline_id, discipline.name, new_name])
                self.__discipline_service.update_discipline(discipline_id, new_name)

    def __ui_print_disciplines(self):  # dont have to undo
        all_disciplines = self.__discipline_service.get_all_disciplines()
        if all_disciplines is not None:
            repository_string_form = ""
            for discipline in all_disciplines:
                repository_string_form += str(discipline)
                repository_string_form += '\n'
            print(repository_string_form)

    def __ui_add_grade(self):  # undoed
        try:
            discipline_id = int(input("Please introduce the discipline_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        try:
            student_id = int(input("Please introduce the student_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        try:
            grade_value = int(input("Please introduce the grade: ").strip())
        except ValueError as ve:
            print(ve)
            return
        self.__grade_service.add_grade(str(discipline_id), str(student_id), grade_value)
        self.__undo_redo_service.add_command_to_stack("addGrade", [str(discipline_id), str(student_id), grade_value])

    def __ui_print_list_of_grades(self):
        all_grades = self.__grade_service.get_all_grades()
        if all_grades is not None:
            repository_string_form = ""
            for grade in all_grades:
                repository_string_form += str(grade)
                repository_string_form += '\n'
            print(repository_string_form)

    def __ui_search_student_by_id(self):
        try:
            student_id = int(input("Please introduce the student_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        student_id = str(student_id)
        list_of_students = self.__student_service.search_student_by_id(student_id)
        for student in list_of_students:
            print(student)

    def __ui_search_student_by_name(self):
        student_name = input("Please introduce the name: ").strip()
        list_of_students = self.__student_service.search_student_by_name(student_name)
        for student in list_of_students:
            print(student)

    def __ui_search_discipline_by_id(self):
        try:
            discipline_id = int(input("Please introduce the discipline_id: ").strip())
        except ValueError as ve:
            print(ve)
            return
        discipline_id = str(discipline_id)
        list_of_disciplines = self.__discipline_service.search_discipline_by_id(discipline_id)
        for discipline in list_of_disciplines:
            print(discipline)

    def __ui_search_discipline_by_name(self):
        discipline_name = input("Please introduce the name: ").strip()
        list_of_disciplines = self.__discipline_service.search_discipline_by_name(discipline_name)
        for discipline in list_of_disciplines:
            print(discipline)

    def __ui_print_disciplines_descending_averages(self):
        list_disciplines_descending_averages = self.__grade_service.list_disciplines_descending_averages()
        if list_disciplines_descending_averages is not None:
            repository_string_form = ""
            for discipline in list_disciplines_descending_averages:
                repository_string_form += str(discipline)
                repository_string_form += '\n'
            print(repository_string_form)

    def __ui_print_failing_students(self):
        list_failing_students = self.__grade_service.list_failing_students()
        if list_failing_students is not None:
            repository_string_form = ""
            for student in list_failing_students:
                repository_string_form += str(student)
                repository_string_form += '\n'
            print(repository_string_form)

    def __ui_print_students_best_school_situation(self):
        list_of_students_by_average_score = self.__grade_service.list_students_descending_averages()
        if list_of_students_by_average_score is not None:
            repository_string_form = ""
            for student in list_of_students_by_average_score:
                repository_string_form += str(student)
                repository_string_form += '\n'
            print(repository_string_form)

    def start(self):
        self.__print_menu()
        while True:
            command = input(">>>")
            if command.upper() == "EXIT":
                break
            elif command.upper() == "MENU":
                self.__print_menu()
            elif command.upper() == "UNDO":
                try:
                    self.__undo_redo_service.call_undo()
                    print("Undo operation went successfully!")
                except UndoError as ue:
                    print("UndoError: " + str(ue))
            elif command.upper() == "REDO":
                try:
                    self.__undo_redo_service.call_redo()
                    print("Redo operation went successfully!")
                except UndoError as ue:
                    print("UndoError: " + str(ue))
            else:
                try:
                    self.__commands[command]()
                except KeyError:
                    print(f"Command {command} not found.")
                except StudentsRegisterManagementException as srme:
                    print(srme)
