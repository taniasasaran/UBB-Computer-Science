#
# Write the implementation for A2 in this file
#


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values
# print('Hello A2'!) -> prints aren't allowed here!
"""
    Implement a menu-driven console application that provides the following functionalities:
1.Read a list of complex numbers (in z = a + bi form) from the console.
2.Display the entire list of numbers on the console.
3.Display on the console the longest sequence that observes a given property. Each student will receive 2 of the
properties from the list provided below.
    Properties:
        Consecutive number pairs have equal sum. (e.g. 1+3i, 1-i, 1+3i, 1-i)
        Sum of its elements is 10+10i
4.Exit the application.
"""


def create_complex_number(real_part, imaginary_part):
    """
    This function creates a representation of a complex number in the form of a dictionary
    :param real_part:
    :param imaginary_part:
    :return: a dictionary
    """
    complex_number = {"real part": real_part, "imaginary part": imaginary_part}
    return complex_number


def get_real_part(complex_number):
    return complex_number["real part"]


def set_real_part(complex_number, new_real_part):
    complex_number["real part"] = new_real_part


def get_imaginary_part(complex_number):
    return complex_number["imaginary part"]


def set_imaginary_part(complex_number, new_imaginary_part):
    complex_number["imaginary part"] = new_imaginary_part


def sum_two_complex(complex_number_1, complex_number_2):
    """
    This function returns the sum of two complex numbers in a dictionary
    :param complex_number_1:
    :param complex_number_2:
    :return: the sum of the two parameters
    """
    real_part = get_real_part(complex_number_1) + get_real_part(complex_number_2)
    imaginary_part = get_imaginary_part(complex_number_1) + get_imaginary_part(complex_number_2)
    return create_complex_number(real_part, imaginary_part)


def are_equal_two_complex(complex_number_1, complex_number_2):
    """
    This function tests if two complex numbers are equal and returns a bool value
    :param complex_number_1:
    :param complex_number_2:
    :return: True if complex_number_1=complex_number_2, otherwise False
    """
    return get_real_part(complex_number_1) == get_real_part(complex_number_2) and get_imaginary_part(complex_number_1) == get_imaginary_part(complex_number_2)


def get_longest_sequence_with_property(list_of_elements, chosen_property):
    """
    This function searches for the longest sequence that has a given property
    len(list_of_elements), len(list_of_elements) - 1,... ,...
    [1,2,3,4,5,6,7,8] [1,2,3,4,5,6,7] [2,3,4,5,6,7,8]
    :param list_of_elements: the entire list of elements
    :param chosen_property: a function
    :return: the sequence found in form of a list
    """
    initial_length = len(list_of_elements)
    while initial_length > 0:
        for start in range(len(list_of_elements) - initial_length + 1):
            # in range (1) => i=0
            # in range (2) => i=0,1
            end = start + initial_length
            check_list = list_of_elements[start: end]
            if chosen_property(check_list):
                return check_list
        initial_length -= 1
    return []


def check_consecutive_pairs_with_same_sum(list_to_check):
    """
    This function checks if the given list of elements has the property that consecutive number pairs have equal sum
    :param list_to_check: a sequence in form of a list from the entire list of elements(from the get_longest_sequence_with_property)
    :return: True or False
    """
    list_length = len(list_to_check)
    if list_length <= 1:
        return True
    sum_value = sum_two_complex(list_to_check[0], list_to_check[1])
    for i in range(list_length - 1):
        current_sum = sum_two_complex(list_to_check[i], list_to_check[i + 1])
        if not are_equal_two_complex(sum_value, current_sum):
            return False
    return True


def is_sum_equal_to_10_10i(list_to_check):
    """
    This function checks if the given list of elements has the property that the sum of its elements(in complex form)
    is equal to 10+10i
    :param list_to_check: a sequence in form of a list from the entire list of elements (get_longest_sequence_with_property)
    :return: True or False
    """
    list_length = len(list_to_check)
    total_sum = create_complex_number(0, 0)
    sum_theoretical_value = create_complex_number(10, 10)
    for i in range(list_length):
        total_sum = sum_two_complex(list_to_check[i], total_sum)
    return are_equal_two_complex(total_sum, sum_theoretical_value)


def transform_complex_number_string_to_dictionary(string_form):
    """
    This function transforms a complex number from its string form to its dictionary form
    :param string_form: a string which represents the complex number in its string form
    : string_tokens: a list with 1, 2 strings split by + (a complex number can have 0 or 1 +s)
    : string_tokens_split: a list with 1, 2 strings split by - (a complex number can have 0, 1 or 2 -s)
    : check_tokens: a list with 1 or 2 strings(see example)(used to check whether the string represented a real or an imaginary number)
    :return: returns to the function create_complex_number(real_part, imaginary_part) with float parameters
    """
    string_form = string_form.strip()
    string_tokens = string_form.split('+')
    if len(string_tokens) == 1:
        # -1-4i -> string_tokens['-1-4i']
        string_tokens_split = string_tokens[0].split('-')
        if len(string_tokens_split) == 1:
            string_tokens_split[0] = string_tokens_split[0].strip()
            check_tokens = string_tokens_split[0].split('i')
            # 1 -> check_tokens = ['1']
            # 2i -> check_tokens = ['2', '']
            if len(check_tokens) == 1:
                real_part = float(check_tokens[0])
                imaginary_part = 0
                return create_complex_number(real_part, imaginary_part)
            elif len(check_tokens) == 2:
                real_part = 0
                if check_tokens[0] == '':
                    imaginary_part = 1.0
                else:
                    imaginary_part = float(check_tokens[0])
                return create_complex_number(real_part, imaginary_part)
            else:
                pass
        if len(string_tokens_split) == 2:
            # 7-i -> string_tokens_split=['7', 'i'] -> imaginary_tokens=['', '']
            # 6-8i -> string_tokens_split=['6', '8i'] -> imaginary_tokens=['8','']
            string_tokens_split[0] = string_tokens_split[0].strip()
            if string_tokens_split[0] == '':
                real_part = 0
            else:
                real_part = float(string_tokens_split[0])
            string_tokens_split[1] = string_tokens_split[1].strip()
            imaginary_tokens = string_tokens_split[1].split('i')
            imaginary_tokens[0] = imaginary_tokens[0].strip()
            if imaginary_tokens[0] == '':
                imaginary_part = -1.0
            else:
                imaginary_part = -float(imaginary_tokens[0])
            return create_complex_number(real_part, imaginary_part)
        if len(string_tokens_split) == 3:
            string_tokens_split[1] = string_tokens_split[1].strip()
            string_tokens_split[2] = string_tokens_split[2].strip()
            real_part = -float(string_tokens_split[1])
            imaginary_tokens = string_tokens_split[2].split('i')
            # -8-i -> string_tokens_split=['', '8', 'i'] -> imaginary_tokens=['', '']
            # -5-2i -> string_tokens_split=['', '5', '2i'] -> imaginary_tokens=['2', '']
            imaginary_tokens[0] = imaginary_tokens[0].strip()
            if imaginary_tokens[0] == '':
                imaginary_part = -1.0
            else:
                imaginary_part = -float(imaginary_tokens[0])
            return create_complex_number(real_part, imaginary_part)
    elif len(string_tokens) == 2:
        # 4+6i --> string_tokens = ['4', '6i']
        string_tokens[0] = string_tokens[0].strip()
        string_tokens[1] = string_tokens[1].strip()
        real_part = float(string_tokens[0])
        imaginary_tokens = string_tokens[1].split('i')
        # i -> imaginary_tokens['', '']
        # 6i -> imaginary_tokens['6', '']
        if imaginary_tokens[0] == '':
            imaginary_part = 1.0
        else:
            imaginary_part = float(imaginary_tokens[0])
        return create_complex_number(real_part, imaginary_part)
    else:
        pass


def init_complex_list():
    """
    This function adds the numbers from the list_of_init_complex_numbers_string (string form)  to the final list
    (list_of_init_complex_numbers)(dictionary form). Practically, it initialises the list with 10 numbers.
    Also, this function calls the transform_complex_number_string_to_dictionary function to transform strings to variables.
    """
    list_of_init_complex_numbers_string = ['6+6i', '2+2i', '6+6i', '2+2i', '1+i', '-i', '1', '2i', '10i', '10']
    list_of_init_complex_numbers = []
    for number in list_of_init_complex_numbers_string:
        complex_form = transform_complex_number_string_to_dictionary(number)
        list_of_init_complex_numbers.append(complex_form)
    return list_of_init_complex_numbers


# UI section
# (write all functions that have input or print statements here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def read_complex_list():
    """
    This function reads a list of complex numbers(in string form), calls the transform_complex_number to transform them
    into dictionary form adds them to the pre-existent list (already containing 10 numbers) and returns the final list
    :return: the final list of numbers
    """
    print("\nEnter your numbers, split by comma\n")
    numbers_read = input()
    list_of_numbers_string_form = numbers_read.strip().split(',')
    for number in list_of_numbers_string_form:
        number.strip()
    list_of_numbers = init_complex_list()
    for number in list_of_numbers_string_form:
        complex_form = transform_complex_number_string_to_dictionary(number)
        list_of_numbers.append(complex_form)
    return list_of_numbers


def print_complex_number(complex_number):
    """
    This function gets the number in its dictionary form and prints a string represented by its complex form
    :param complex_number: a dictionary
    :return: a "a+bi" string
    """
    # string = str(get_real_part(complex_number)) + str(get_imaginary_part(complex_number)) + "i"
    if get_imaginary_part(complex_number) >= 0:
        sign = "+"
    else:
        sign = ""
    real_part = get_real_part(complex_number)
    imaginary_part = get_imaginary_part(complex_number)
    if real_part == int(real_part):
        real_part = int(real_part)
    if imaginary_part == int(imaginary_part):
        imaginary_part = int(imaginary_part)
    if imaginary_part == 1:
        if real_part == 0:
            print(f"{sign}i")
        else:
            print(f"{real_part}{sign}i")
    elif imaginary_part == -1:
        if real_part == 0:
            print(f"-i")
        else:
            print(f"{real_part}-i")
    elif imaginary_part == 0:
        print(f"{real_part}")
    elif real_part == 0 and imaginary_part < 0:
        print(f"{sign}{imaginary_part}i")
    elif real_part == 0 and imaginary_part >= 0:
        print(f"{imaginary_part}i")
    else:
        print(f"{real_part}{sign}{imaginary_part}i")


def print_menu():
    print("\nApplication menu: ")
    print("    1 to introduce a list of complex numbers (in a + bi form)")
    print("    2 to display the entire list of numbers")
    print(
        "    3 to display the longest sequence that observes the property that consecutive number pairs have equal sum.")
    print("    4 to display the longest sequence that observes the property that the sum of its elements is 10+10i")
    print("    0 exit")
    print("command:")


def main():
    list_of_complex_numbers = init_complex_list()
    done = False
    while not done:
        print_menu()
        command = int(input())
        if command == 1:
            list_of_complex_numbers = read_complex_list()
        elif command == 2:
            print("\nThe entire list of complex numbers is:")
            for number in list_of_complex_numbers:
                print_complex_number(number)
        elif command == 3:
            print("\nThe longest sequence that observes the property that consecutive number pairs have equal sum is:")
            longest_list = get_longest_sequence_with_property(list_of_complex_numbers,
                                                              check_consecutive_pairs_with_same_sum)
            for number in longest_list:
                print_complex_number(number)
        elif command == 4:
            print("\nThe longest sequence that observes the property that the sum of its elements is 10+10i is:")
            longest_list = get_longest_sequence_with_property(list_of_complex_numbers, is_sum_equal_to_10_10i)
            for number in longest_list:
                print_complex_number(number)
        elif command == 0:
            done = True
        else:
            print("\nWrong command!")


main()
