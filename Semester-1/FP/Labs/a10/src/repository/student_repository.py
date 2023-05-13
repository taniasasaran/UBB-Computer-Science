import pickle
from copy import deepcopy

from src.domain.student import Student
from src.domain.validators_and_errors import StudentRepositoryError
from src.repository.iterable_structure import Collection


class StudentRepository:
    def __init__(self, student_validator_class):
        self.data = Collection()
        self.__validator_class = student_validator_class

    def add_20_students_in_repository(self):
        """
            This function adds 20 students in the repository
            :return: none
        """
        list_of_names = ["Liam", "Olivia", "Noah", "Emma", "Oliver", "Ava", "Elijah", "Charlotte", "William",
                         "Sophia", "James", "Amelia", "Benjamin", "Isabella", "Lucas", "Mia", "Henry", "Evelyn",
                         "Alexander", "Harper"]
        i = 0
        for name in list_of_names:
            student = Student(str(i + 1), name)
            i = i + 1
            self.add_student(student)

    def student_id_existence(self, id_to_be_checked):
        """
        This function checks if a student with a specified ID is in repository or not
        :param id_to_be_checked: a string
        :return: True or False
        """
        for student in self.data:
            if student.student_id == id_to_be_checked:
                return True
        return False

    def add_student(self, student):
        """
        This function adds a new student in the repository if the parameters are valid, otherwise it raises an error
        :param student: an object(class)
        :return: none
        """
        self.__validator_class.validate(student)
        if self.student_id_existence(student.student_id):
            raise StudentRepositoryError(f"Student with ID={student.student_id} already exists!")
        self.data.__add__(student)

    def remove_student(self, student_to_be_removed_id):
        """
        This function removes a student from the repository if the parameters are valid, otherwise it raises an error
        :param student_to_be_removed_id: a string
        :return: none
        """
        if not self.student_id_existence(student_to_be_removed_id):
            raise StudentRepositoryError(f"Student with ID={student_to_be_removed_id} does not exist!")
        for i, student in enumerate(self.data):
            if student.student_id == student_to_be_removed_id:
                del self.data[i]
                break

    def update_student(self, student_to_be_updated_id, new_name):
        """
        This function changes the data from the repository
        :param student_to_be_updated_id: a string
        :param new_name: a string
        :return:
        """
        if not self.student_id_existence(student_to_be_updated_id):
            raise StudentRepositoryError(f"Student with ID={student_to_be_updated_id} does not exist!")
        for position in range(len(self.data)):
            if self.data[position].student_id == student_to_be_updated_id:
                self.data[position].name = new_name

    def search_student_by_id(self, student_id):
        """
            This function gets all the students which have the "student_id" contained in their student_id
            :param student_id: a string
            :return: a list of strings
        """
        list_matched_students = list()
        for student in self.data:
            if student_id in student.student_id:
                list_matched_students.append(str(student))
        return list_matched_students

    def find_student_by_id(self, student_id):
        """
        This function gets the student's attributes based on its student_id
        :param student_id: a string
        :return: a list consisting of student.student_id and student.name
        """
        student_parameters = list()
        for student in self.data:
            if student_id == student.student_id:
                student_parameters.append(student.student_id)
                student_parameters.append(student.name)
        return student_parameters

    def search_student_by_name(self, student_name):
        """
            This function gets all the students which have the "student_name" contained in their name
            :param student_name: a string
            :return: a list of strings
        """
        list_matched_students = list()
        for student in self.data:
            if student_name.lower() in student.name.lower():
                list_matched_students.append(str(student))
        return list_matched_students

    def get_all_str(self):
        """
        This function returns the contents of the repository in form of a list of strings
        :return: a list of strings
        """
        repository_list_form = list()
        for item in self.data:
            repository_list_form.append(str(item))
        return repository_list_form

    def get_all_students(self):
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


class StudentBinFileRepository(StudentRepository):
    def __init__(self, student_validator_class, file_name):
        super().__init__(student_validator_class)
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

    def add_student(self, student):
        """
        1. Inherit all the functions and methods of the StudentRepository
        2. Save the students to file
        """
        if super(StudentBinFileRepository, self).student_id_existence(student.student_id):
            raise StudentRepositoryError(f"Student with id={student.student_id} already exists!")
        self.data += [student]
        self._save_file()

    def update_student(self, student_to_be_updated_id, new_name):
        if not super(StudentBinFileRepository, self).student_id_existence(student_to_be_updated_id):
            raise StudentRepositoryError(f"Student with id={student_to_be_updated_id} does not exist!")
        super(StudentBinFileRepository, self).update_student(student_to_be_updated_id, new_name)
        self._save_file()

    def remove_student(self, student_to_be_removed_id):
        if not super(StudentBinFileRepository, self).student_id_existence(student_to_be_removed_id):
            raise StudentRepositoryError(f"Student with id={student_to_be_removed_id} does not exist!")
        super(StudentBinFileRepository, self).remove_student(student_to_be_removed_id)
        self._save_file()

    def __len__(self):
        return self.data.__len__()


# ==============================


class StudentTextFileRepository(StudentRepository):
    def __init__(self, student_validator_class, file_name):
        super().__init__(student_validator_class)
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        file = open(self._file_name, "rt")  # rt -> read, text-mode
        for line in file.readlines():
            _student_id, name = line.split(maxsplit=1, sep=',')
            name = name.replace('\n', "")
            super(StudentTextFileRepository, self).add_student(Student(int(_student_id), name.rstrip()))
        file.close()

    def _save_file(self):
        file = open(self._file_name, "wt")  # wt -> write, text-mode

        for student in self.data:
            file.write(str(student.student_id) + ',' + student.name + "\n")

        file.close()

    def add_student(self, student):
        """
        1. Do whatever the add method in the base class does
        2. Save the students to file
        """
        super(StudentTextFileRepository, self).add_student(student)
        self._save_file()

    def update_student(self, student_to_be_updated_id, new_name):
        super(StudentTextFileRepository, self).update_student(student_to_be_updated_id, new_name)
        self._save_file()

    def remove_student(self, student_to_be_removed_id):
        super(StudentTextFileRepository, self).remove_student(student_to_be_removed_id)
        self._save_file()

    def __len__(self):
        return self.data.__len__()
