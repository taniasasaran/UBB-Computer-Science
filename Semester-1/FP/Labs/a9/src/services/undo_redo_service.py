from src.domain.validators_and_errors import UndoError


class UndoRedoManager:
    """
    Class to take care of the undo/redo functionalities
    """
    def __init__(self, student_service, discipline_service, grade_service):
        self.__student_service = student_service
        self.__discipline_service = discipline_service
        self.__grade_service = grade_service

        self.__commandStackTop = -1
        self.__commandStack = []

        self.__undoDictionary = {
            "sAdd": self.undo_add_student,
            "sRemove": self.undo_remove_student,
            "sUpdate": self.undo_update_student,
            "dAdd": self.undo_add_discipline,
            "dRemove": self.undo_remove_discipline,
            "dUpdate": self.undo_update_discipline,
            "delete": self.undo_remove_grade,
            "cascade": self.undo_cascade_remove,
            "addGrade": self.undo_add_grade
        }

        self.__redoDictionary = {
            "sAdd": self.redo_add_student,
            "sRemove": self.redo_remove_student,
            "sUpdate": self.redo_update_student,
            "dAdd": self.redo_add_discipline,
            "dRemove": self.redo_remove_discipline,
            "dUpdate": self.redo_update_discipline,
            "delete": self.redo_remove_grade,
            "cascade": self.redo_cascade_remove,
            "addGrade": self.redo_add_grade
        }

    """
    Undo functionalities
    """
    def get_stack(self):
        return self.__commandStack

    def add_command_to_stack(self, action, target_object):
        self.__commandStackTop += 1
        self.__commandStack.insert(self.__commandStackTop, [action, target_object])
        del self.__commandStack[self.__commandStackTop + 1:]

    def get_last_operation(self):
        operation = self.__commandStack[self.__commandStackTop]
        self.__commandStackTop -= 1
        return operation

    @staticmethod
    def get_last_operation_command(operation):
        return operation[0]

    @staticmethod
    def get_last_operation_object(operation):
        return operation[1]

    def get_next_operation(self):
        operation = self.__commandStack[self.__commandStackTop + 1]
        self.__commandStackTop += 1
        return operation

    def call_undo(self):
        if self.__commandStackTop == -1:
            raise UndoError("There is nothing to undo.")
        last_operation = self.get_last_operation()
        action = self.get_last_operation_command(last_operation)
        target_object = self.get_last_operation_object(last_operation)
        self.__undoDictionary[action](target_object)

    def undo_add_student(self, student):
        """
        Undoes the action of adding a student
        """
        self.__student_service.remove_student(student.student_id)

    def undo_remove_student(self, student):
        """
        Undoes the action of removing a student
        """
        self.__student_service.add_student(student.student_id, student.name)

    def undo_cascade_remove(self, operations):
        """
        Undoes the cascade removal of a student or a discipline
        """
        new_operations = operations[:]
        while len(new_operations) > 0:
            operation = new_operations.pop()
            action = self.get_last_operation_command(operation)
            target_object = self.get_last_operation_object(operation)
            self.__undoDictionary[action](target_object)

    def undo_update_student(self, student):
        """
        Undoes the action of updating a student
        """
        self.__student_service.update_student(student[0], student[1])

    def undo_add_discipline(self, discipline):
        """
        Undoes the action of adding a discipline
        """
        self.__discipline_service.remove_discipline(discipline.discipline_id)

    def undo_remove_discipline(self, discipline):
        """
        Undoes the action of removing a discipline
        """
        self.__discipline_service.add_discipline(discipline.discipline_id, discipline.name)

    def undo_update_discipline(self, discipline):
        """
        Undoes the action of updating a discipline
        """
        self.__discipline_service.update_discipline(discipline[0], discipline[1])

    def undo_add_grade(self, parameters):
        """
        Undoes the action of adding a grade
        """
        self.__grade_service.remove_grade(parameters[0], parameters[1])

    def undo_remove_grade(self, grade):
        """
        grade[0] --> discipline_id
        grade[1] --> student_id
        grade[2] --> grade_value
        """
        self.__grade_service.add_grade(grade[0], grade[1], grade[2])

    """
    Redo functionalities
    """
    def call_redo(self):
        if self.__commandStackTop == len(self.__commandStack) - 1:
            raise UndoError("There is nothing to redo!")
        next_operation = self.get_next_operation()
        action = self.get_last_operation_command(next_operation)
        target_object = self.get_last_operation_object(next_operation)
        self.__redoDictionary[action](target_object)

    def redo_add_student(self, student):
        self.undo_remove_student(student)

    def redo_remove_student(self, student):
        self.undo_add_student(student)

    def redo_cascade_remove(self, operations):
        for item in operations:
            action = self.get_last_operation_command(item)
            target_object = self.get_last_operation_object(item)
            self.__redoDictionary[action](target_object)

    def redo_update_student(self, student):
        self.__student_service.update_student(student[0], student[2])

    def redo_add_discipline(self, discipline):
        self.undo_remove_discipline(discipline)

    def redo_remove_discipline(self, discipline):
        self.undo_add_discipline(discipline)

    def redo_update_discipline(self, discipline):
        self.__discipline_service.update_discipline(discipline[1], discipline[2])

    def redo_add_grade(self, parameters):
        self.__grade_service.add_grade(parameters[0], parameters[1], parameters[2])

    def redo_remove_grade(self, grade):
        self.__grade_service.remove_grade(grade[0], grade[1])
