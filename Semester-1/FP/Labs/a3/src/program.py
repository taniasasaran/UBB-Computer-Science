"""
  Write non-UI functions below
"""


def create_apartment(apartments, apartment_number, water, heating, gas, electricity, other):
    """
    This function creates a representation of an apartment's expenses in the form of a dictionary
    :param apartment_number: an integer larger or equal to 1 representing the number of apartment which
                             has the following expenses
    :param water: an integer larger than 0 representing the water expense
    :param heating: an integer larger than 0 representing the heating expense
    :param gas: an integer larger than 0 representing the gas expense
    :param electricity: an integer larger than 0 representing the electricity expense
    :param other: an integer larger than 0 representing the other expenses
    :return: a dictionary containing the values for each expense type
    """
    apartment = {"apartment_number": apartment_number, "water": water, "heating": heating, "gas": gas,
                 "electricity": electricity, "other": other}
    apartments.append(apartment)


def set_expense(apartment, type, new_expense):
    """
    This function represents a setter for each entity in the dictionary of an apartment.
    :param apartment: the number of apartment for which we want to change the expense
    :param type: the type of expense we want to change
    :param new_expense: the new value of that expense
    :return None; this function only modifies data in the dictionary
    """
    apartment[type] = new_expense


def get_expense(apartment, type):
    """
    This function represents a getter for each entity in the dictionary of an apartment.
    :param apartment: the number of apartment from which we want the expense
    :param type: the type of expense we want to get
    :return an integer >= 0 representing the value of that expense type in a given apartment
    """
    return apartment[type]


def initialize_list_of_apartments():
    """
    This function adds apartments(in dictionary form) to the list of all apartments in the building
    return: the complete list
    """
    apartments = []
    for i in range(10):
        create_apartment(apartments, i + 1, 0, 0, 0, 0, 0)
    return apartments


def test_initialize_list_of_apartments():
    assert initialize_list_of_apartments() == [
        {'apartment_number': 1, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 2, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 3, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 4, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 5, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 6, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 7, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 8, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 9, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0},
        {'apartment_number': 10, 'water': 0, 'heating': 0, 'gas': 0, 'electricity': 0, 'other': 0}]


def add_values_in_initialization():
    """
    This function adds values in the list of dictionaries containing data about all the apartments in the building
    In this case, it changes the values of expenses of 10 apartments
    TRY: send a parameter number_of_apartments ; for i in range(1,number_of_apartments+1): ...
    """
    apartments = initialize_list_of_apartments()
    types_of_expenses = ['water', 'heating', 'gas', 'electricity', 'other']
    for i in range(1, 11):
        for type in types_of_expenses:
            set_expense(apartments[i - 1], type, i + 9)
    return apartments


def test_add_values_in_initialization():
    assert add_values_in_initialization() == [
        {'apartment_number': 1, 'water': 10, 'heating': 10, 'gas': 10, 'electricity': 10, 'other': 10},
        {'apartment_number': 2, 'water': 11, 'heating': 11, 'gas': 11, 'electricity': 11, 'other': 11},
        {'apartment_number': 3, 'water': 12, 'heating': 12, 'gas': 12, 'electricity': 12, 'other': 12},
        {'apartment_number': 4, 'water': 13, 'heating': 13, 'gas': 13, 'electricity': 13, 'other': 13},
        {'apartment_number': 5, 'water': 14, 'heating': 14, 'gas': 14, 'electricity': 14, 'other': 14},
        {'apartment_number': 6, 'water': 15, 'heating': 15, 'gas': 15, 'electricity': 15, 'other': 15},
        {'apartment_number': 7, 'water': 16, 'heating': 16, 'gas': 16, 'electricity': 16, 'other': 16},
        {'apartment_number': 8, 'water': 17, 'heating': 17, 'gas': 17, 'electricity': 17, 'other': 17},
        {'apartment_number': 9, 'water': 18, 'heating': 18, 'gas': 18, 'electricity': 18, 'other': 18},
        {'apartment_number': 10, 'water': 19, 'heating': 19, 'gas': 19, 'electricity': 19, 'other': 19}]


def add_new_transaction(apartments, apartment_number, type, amount):
    """
    This function increases the value of a certain TYPE of expense(water, heating, electricity or other) with an AMOUNT
    for a given APARTMENT_NUMBER
    apartments: the list of dictionaries containing data about all the apartments in the building
    amount: an integer greater than 0
    apartment_number: an integer greater or equal to 1, but smaller or equal to the number of apartments
    return: None; this function changes the data in the big list of apartments' expenses
    """
    new_amount = get_expense(apartments[int(apartment_number) - 1], type) + int(amount)
    set_expense(apartments[int(apartment_number) - 1], type, new_amount)


def remove_expenses(apartments, list_of_apartments_in_command, list_of_types_in_command):
    """
    This function removes expenses for:
    i) all apartments if we get only one parameter representing the type of expense
    ii) one or several apartments (we get only one parameter representing the list_of_apartments_in_command)

    apartments: the list of dictionaries containing data about all the apartments in the building
    list_of_apartments_in_command: can be a list with one or more elements OR the string "all"
    list_of_types_in_command: can be a list with one or more elements OR None
    return: None; this function changes the data in the big list of apartments' expenses
    """
    if list_of_apartments_in_command == "all":
        number_of_apartments = len(apartments) + 1
        list_of_apartments_in_command = [i for i in range(1, number_of_apartments)]
    list_of_types_to_be_removed = ["water", "heating", "gas", "electricity", "other"]
    if len(list_of_types_in_command) == 1:
        list_of_types_to_be_removed = [list_of_types_in_command]
    for apartment_number in list_of_apartments_in_command:
        for type in list_of_types_to_be_removed:
            set_expense(apartments[int(apartment_number) - 1], type, 0)


def replace_expense(apartments, apartment_number, type, amount):
    """
    This function changes the value of a given's type of expense of a given's apartment_number to a new amount
    apartments: the list of dictionaries containing data about all the apartments in the building
    apartment_number: an integer greater or equal to 1, but smaller or equal to the number of apartments
    type: a string
    amount: the new value of that type of expense of that apartment
    return: None; this function changes the data in the big list of apartments' expenses
    """
    set_expense(apartments[int(apartment_number) - 1], type, amount)


def sum_of_total_expenses_of_an_apartment(apartments, apartment_number):
    """
    This function computes and returns the sum of all expenses of an apartment
    apartments: the list of dictionaries containing data about all the apartments in the building
    apartment_number: an integer greater or equal to 1, but smaller or equal to the number of apartments
    return: an integer >=0
    """
    list_of_types = ["water", "heating", "gas", "electricity", "other"]
    sum_of_total_expenses = 0
    for type in list_of_types:
        sum_of_total_expenses += int(get_expense(apartments[int(apartment_number)], type))
    return sum_of_total_expenses


def test_sum_of_total_expenses_of_an_apartment():
    apartment = add_values_in_initialization()
    assert sum_of_total_expenses_of_an_apartment(apartment, 4) == 70


def create_list_of_apartments_that_have_property(apartments, property, amount):
    """
    This function creates a list of apartments that have the sum of all their expenses smaller, greater
    or equal to a given amount
    apartments: the list of dictionaries containing data about all the apartments in the building
    property: '<', '>', '='
    amount: an integer
    return: a list or None (if the list is empty)
    """
    list_of_apartments_with_property = []
    if property == '=':
        for i in range(10):
            if int(sum_of_total_expenses_of_an_apartment(apartments, i)) == int(amount):
                list_of_apartments_with_property.append(i + 1)
    elif property == '>':
        for i in range(10):
            if int(sum_of_total_expenses_of_an_apartment(apartments, i)) > int(amount):
                list_of_apartments_with_property.append(i + 1)
    elif property == '<':
        for i in range(10):
            if int(sum_of_total_expenses_of_an_apartment(apartments, i)) < int(amount):
                list_of_apartments_with_property.append(i + 1)
    if list_of_apartments_with_property == []:
        return None
    return list_of_apartments_with_property


def test_create_list_of_apartments_that_have_property():
    apartment = add_values_in_initialization()
    assert create_list_of_apartments_that_have_property(apartment, "=", 90) == [9]
    assert create_list_of_apartments_that_have_property(apartment, ">", 100) == None


def display_apartments_with_expenses_having_different_properties(apartments, apartment_number, property, amount):
    """
    This function returns a list of apartments that have a certain property:
    i) property=None and apartment_number=None then it returns the entire list of apartments
    ii) property=['<', '>', '='] then it returns a list that contains apartments that have the sum
        of all their expenses greater, smaller or equal to a given amount
    iii) property=None and apartment_number!=None then it returns all the expenses of an apartment
    apartments: the list of dictionaries containing data about all the apartments in the building
    """
    if apartment_number == None and property == None and amount == None:
        return apartments
    if not apartment_number == None:
        return apartments[int(apartment_number) - 1]
    if apartment_number == None and not property == None and not amount == None:
        return create_list_of_apartments_that_have_property(apartments, property, amount)


def test_display_apartments_with_expenses_having_different_properties():
    apartment = add_values_in_initialization()
    assert display_apartments_with_expenses_having_different_properties(apartment, None, '=', 60) == [3]
    assert display_apartments_with_expenses_having_different_properties(apartment, 5, None, None) == {
        'apartment_number': 5, 'water': 14, 'heating': 14, 'gas': 14, 'electricity': 14, 'other': 14}


############################################### split, validate and get functions for each operation #############################################

def split_command_parameters(command_parameters):
    """
    This function splits the command's parameters(so no command_word) into smaller parameters if the string
    command_parameters is not None,
    else None
    command_parameters: a string with 0, 1, ..., 4 words
    return: a list consisting of the all words/numbers from that string
    """
    if command_parameters is not None:
        command_parameters = command_parameters.strip()
        parameter_tokens = command_parameters.split()
        return parameter_tokens
    return None


def test_split_command_parameters():
    assert split_command_parameters(None) == None
    assert split_command_parameters('5') == ['5']
    assert split_command_parameters('25 gas 100') == ['25', 'gas', '100']
    assert split_command_parameters('12 gas with 200') == ['12', 'gas', 'with', '200']


def validate_add_command_parameters(apartments, command_parameters):
    """
    This function validates the parameters introduced for the add function
    It raises errors if there are problems
    apartments: the list of dictionaries containing data about all the apartments in the building
    command_parameters: a string (or None)
    return: none or raise value errors
    """
    if command_parameters is None:
        raise ValueError(f"Bad command! Please introduce parameters!")
    parameter_tokens = split_command_parameters(command_parameters)
    list_of_types = ["water", "heating", "gas", "electricity", "other"]
    if command_parameters is not None:
        if not len(parameter_tokens) == 3 or not int(parameter_tokens[0]) >= 1 or not int(parameter_tokens[0]) <= len(
                apartments) or not parameter_tokens[1] in list_of_types or not int(parameter_tokens[2]) >= 0:
            raise ValueError(f"Bad parameters!")


def get_add_command_parameters(command_parameters):
    """
    This function helps extract the parameters and helps the 'add' function to get them easier
    command_parameters: string
    return: a tuple consisting of apartment, type, amount
    """
    parameter_tokens = split_command_parameters(command_parameters)
    apartment = parameter_tokens[0]
    type = parameter_tokens[1]
    amount = parameter_tokens[2]
    return apartment, type, amount


def test_get_add_command_parameters():
    assert get_add_command_parameters('25 gas 100') == ('25', 'gas', '100')


def validate_remove_command_parameters(apartments, command_parameters):
    """
        This function validates the parameters introduced for the remove function
    It raises errors if there are problems
    apartments: the list of dictionaries containing data about all the apartments in the building
    command_parameters: a string (or None)
    return: none or raise value errors
    """
    if command_parameters is None:
        raise ValueError(f"Bad command! Please introduce parameters!")
    parameter_tokens = split_command_parameters(command_parameters)
    if len(parameter_tokens) == 2 or len(parameter_tokens) > 3:
        raise ValueError(f"Bad number of parameters!")
    if len(parameter_tokens) == 3 and not (
            parameter_tokens[1] == "to" and parameter_tokens[0].isnumeric() and parameter_tokens[2].isnumeric()):
        raise ValueError(f"Bad parameters!")
    if len(parameter_tokens) == 3 and not (
            int(parameter_tokens[0]) >= 1 and int(parameter_tokens[0]) < int(parameter_tokens[2]) and int(
            parameter_tokens[2]) <= len(apartments)):
        raise ValueError(f"Bad parameters!")
    list_of_types = ["water", "heating", "gas", "electricity", "other"]
    if len(parameter_tokens) == 1 and not (parameter_tokens[0].isnumeric() or parameter_tokens[0] in list_of_types):
        raise ValueError(f"Bad parameter!")
    if len(parameter_tokens) == 1 and parameter_tokens[0].isnumeric() and not (
            int(parameter_tokens[0]) <= len(apartments)
            or int(parameter_tokens[0]) >= 1):
        raise ValueError(f"Bad parameter!")


def get_remove_command_parameters(command_parameters):
    """
        This function helps extract the parameters and helps the 'remove' function to get them easier
    command_parameters: string
    return: a tuple consisting of the list_of_apartments_in_command, list_of_types_in_command that cannot be both empty
    """
    parameter_tokens = split_command_parameters(command_parameters)
    list_of_types = ["water", "heating", "gas", "electricity", "other"]
    if len(parameter_tokens) == 3:
        list_of_apartments_in_command = [i for i in range(int(parameter_tokens[0]), int(parameter_tokens[2]) + 1)]
        list_of_types_in_command = list_of_types
    elif len(parameter_tokens) == 1 and parameter_tokens[0].isnumeric():
        list_of_apartments_in_command = list(parameter_tokens[0])
        list_of_types_in_command = list_of_types
    else:
        list_of_apartments_in_command = "all"
        list_of_types_in_command = parameter_tokens[0]
    return list_of_apartments_in_command, list_of_types_in_command


def test_get_remove_command_parameters():
    assert get_remove_command_parameters('5') == (['5'], ['water', 'heating', 'gas', 'electricity', 'other'])
    assert get_remove_command_parameters('water') == ('all', 'water')
    assert get_remove_command_parameters('5 to 10') == (
    [5, 6, 7, 8, 9, 10], ['water', 'heating', 'gas', 'electricity', 'other'])


def validate_replace_command_parameters(apartments, command_parameters):
    """
        This function validates the parameters introduced for the replace function
    It raises errors if there are problems
    apartments: the list of dictionaries containing data about all the apartments in the building
    command_parameters: a string (or None)
    return: none or raise value errors
    """
    if command_parameters is None:
        raise ValueError(f"Bad command! Please introduce parameters!")
    parameter_tokens = split_command_parameters(command_parameters)
    list_of_types = ["water", "heating", "gas", "electricity", "other"]
    if not len(parameter_tokens) == 4:
        raise ValueError(f"Bad number of parameters!")
    elif not parameter_tokens[2] == 'with':
        raise ValueError(f"Bad parameters! You have to type 'with'.")
    elif not (parameter_tokens[0].isnumeric() and int(parameter_tokens[0]) >= 1 and int(parameter_tokens[0]) <= len(
            apartments)
              and parameter_tokens[3].isnumeric()):
        raise ValueError(f"Bad parameters!")
    elif not parameter_tokens[1] in list_of_types:
        raise ValueError(f"The type {parameter_tokens[1]} does not exist!")


def get_replace_command_parameters(command_parameters):
    """
        This function helps extract the parameters and helps the 'replace' function to get them easier
    command_parameters: string
    return: a tuple consisting of apartment, type, amount
    """
    parameter_tokens = split_command_parameters(command_parameters)
    apartment = parameter_tokens[0]
    type = parameter_tokens[1]
    amount = parameter_tokens[3]
    return apartment, type, amount


def test_get_replace_command_parameters():
    assert get_replace_command_parameters('12 gas with 200') == ('12', 'gas', '200')


def validate_list_command_parameters(apartments, command_parameters):
    """
         This function validates the parameters introduced for the replace function
    It raises errors if there are problems
    apartments: the list of dictionaries containing data about all the apartments in the building
    command_parameters: a string (or None)
    return: none or raise value errors
    """
    if command_parameters is None:
        return True
    parameter_tokens = split_command_parameters(command_parameters)
    list_of_properties = ['>', '<', '=']
    if len(parameter_tokens) == 1 and (
            not int(parameter_tokens[0]) <= len(apartments) + 1 or not int(parameter_tokens[0]) >= 1):
        raise ValueError(f"The apartment {parameter_tokens[0]} does not exist!")
    elif len(parameter_tokens) == 2 and (
            parameter_tokens[0] not in list_of_properties or not parameter_tokens[1].isnumeric()):
        raise ValueError(f"Bad parameters!")
    elif len(parameter_tokens) >= 3:
        raise ValueError(f"Bad command!")


def get_list_command_parameters(command_parameters):
    """
        This function helps extract the parameters and helps the 'add' function to get them easier
    command_parameters: string
    return: a tuple consisting of apartment_number, type, amount that can be empty or not
    """
    apartment_number = None
    property = None
    amount = None
    if not command_parameters is None:
        parameter_tokens = split_command_parameters(command_parameters)
        if len(parameter_tokens) == 1:
            apartment_number = parameter_tokens[0]
            property = None
            amount = None
        elif len(parameter_tokens) == 2:
            apartment_number = None
            property = parameter_tokens[0]
            amount = parameter_tokens[1]
    return apartment_number, property, amount


def test_get_list_command_parameters():
    assert get_list_command_parameters('15') == ('15', None, None)
    assert get_list_command_parameters('> 100') == (None, '>', '100')
    assert get_list_command_parameters('= 60') == (None, '=', '60')


def split_command(user_command):
    """
        Split the user's command into the command word and a parameters string
        ex:
             add 25 gas 100     -> ('add', '25 gas 100')
             remove 5           -> ('remove', '5')
             list               -> ('list', None)
             replace 12 other with 200  ->('replace', '12 other with 200')

        :param user_command: Command input by the user
        :return: A tuple of (command_word, command_parameters) in lowercase
    """
    user_command = user_command.strip()
    tokens = user_command.split(maxsplit=1)
    command_word = tokens[0].lower() if len(tokens) > 0 else None
    command_parameters = tokens[1].lower() if len(tokens) == 2 else None
    return command_word, command_parameters


def test_split_command():
    assert split_command('list') == ('list', None)
    assert split_command('remove 5') == ('remove', '5')
    assert split_command('add 25 gas 100') == ('add', '25 gas 100')
    assert split_command('replace 12 gas with 200') == ('replace', '12 gas with 200')


################# TESTS #############################

def tests():
    test_initialize_list_of_apartments()
    test_add_values_in_initialization()
    test_sum_of_total_expenses_of_an_apartment()
    test_create_list_of_apartments_that_have_property()
    test_display_apartments_with_expenses_having_different_properties()
    test_split_command_parameters()
    test_get_add_command_parameters()
    test_get_remove_command_parameters()
    test_get_replace_command_parameters()
    test_get_list_command_parameters()
    test_split_command()


"""
  Write the command-driven UI below
"""


def print_commands(commands):
    print(*list(commands)[1:], "exit", sep="\n")


def get_command_line():
    command_line = input("Command> ")
    return command_line


def start_command_ui():
    """
    Command format example for administrator
         add 25 water 100     # add to apartment 25 an expense for water in amount of 100 RON
         remove 5             # remove all expenses for apartment 15
         list                 # display the list of all expenses
    :return:
    """
    apartments = add_values_in_initialization()
    apartment_number = 1
    commands_dictionary = {'apartment_number': apartment_number,
                           'add': (validate_add_command_parameters, get_add_command_parameters, add_new_transaction),
                           'remove': (
                           validate_remove_command_parameters, get_remove_command_parameters, remove_expenses),
                           'replace': (
                           validate_replace_command_parameters, get_replace_command_parameters, replace_expense),
                           'list': (validate_list_command_parameters, get_list_command_parameters,
                                    display_apartments_with_expenses_having_different_properties)}

    while True:
        print_commands(commands_dictionary)
        command_line = get_command_line()
        command_line = command_line.strip()
        if command_line == "exit":
            break

        command, command_list_of_parameters = split_command(command_line)
        try:
            validate_parameters = commands_dictionary[command][0]
            validate_parameters(apartments, command_list_of_parameters)
            get_parameters = commands_dictionary[command][1]
            parameters = get_parameters(command_list_of_parameters)
            commands_dictionary[command][2](apartments, *parameters)
            if command == 'list':
                list = commands_dictionary[command][2](apartments, *parameters)
                if list == None:
                    print(f"None")
                elif command_list_of_parameters == None:
                    print(*list, sep="\n")
                else:
                    print(list)
        except KeyError:
            print(f"Option {command} is not yet implemented")
        except ValueError as ve:
            print(ve)
        except IndexError:
            print(f"List index out of range")


tests()
start_command_ui()
