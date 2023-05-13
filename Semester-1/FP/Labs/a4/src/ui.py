"""
  User interface module
"""
from functions import add_values_in_initialization, split_command, modify_list_of_apartments_with_maximum_values, validate_add_command_parameters, get_add_command_parameters, add_new_transaction, validate_remove_command_parameters, get_remove_command_parameters, remove_expenses,validate_replace_command_parameters, get_replace_command_parameters, replace_expense,validate_list_command_parameters, get_list_command_parameters, display_apartments_with_expenses_having_different_properties,validate_sum_command_parameters, get_sum_command_parameters, sum_of_all_expenses_of_a_given_type,validate_max_command_parameters, get_max_command_parameters, maximum_amount_per_each_expense_type_for_a_given_apartment,validate_sort_command_parameters, get_sort_command_parameters, sort_ascending_by_amount_of_money,validate_filter_command_parameters, get_filter_command_parameters, filter_function,validate_undo_command_parameters, undo_operation
from copy import deepcopy

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
    list_of_apartments_with_maximum_values = deepcopy(apartments)
    list_of_operation_results = []
    list_of_operation_results.append(deepcopy(apartments))
    apartment_number = 1
    commands_dictionary = {'apartment_number': apartment_number,
                           'add': (validate_add_command_parameters, get_add_command_parameters, add_new_transaction),
                           'remove': (validate_remove_command_parameters, get_remove_command_parameters, remove_expenses),
                           'replace': (validate_replace_command_parameters, get_replace_command_parameters, replace_expense),
                           'list': (validate_list_command_parameters, get_list_command_parameters,
                                    display_apartments_with_expenses_having_different_properties),
                           'sum':(validate_sum_command_parameters, get_sum_command_parameters, sum_of_all_expenses_of_a_given_type),
                           'max':(validate_max_command_parameters, get_max_command_parameters, maximum_amount_per_each_expense_type_for_a_given_apartment),
                           'sort':(validate_sort_command_parameters, get_sort_command_parameters, sort_ascending_by_amount_of_money),
                           'filter':(validate_filter_command_parameters, get_filter_command_parameters, filter_function),
                           'undo':(validate_undo_command_parameters, None, undo_operation)}

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
            if get_parameters is not None:
                parameters = get_parameters(command_list_of_parameters)
            if command == 'undo':
                commands_dictionary[command][2](apartments, list_of_operation_results)
            if command == 'max':
                list = commands_dictionary[command][2](list_of_apartments_with_maximum_values, parameters)
                print(list)
            list_of_displaying_commands=['list', 'sort', 'sum']
            if command in list_of_displaying_commands:
                if type(parameters) == str:
                    list = commands_dictionary[command][2](apartments, parameters)
                else:
                    list = commands_dictionary[command][2](apartments, *parameters)
                if list == None:
                    print(f"None")
                elif command_list_of_parameters == None:
                    print(*list, sep="\n")
                else:
                    print(list)
            if type(parameters) == str and not command == 'undo':
                commands_dictionary[command][2](apartments, parameters)
            elif not command == 'undo':
                commands_dictionary[command][2](apartments, *parameters)
            list_of_modifying_commands=['add', 'remove', 'replace', 'filter', 'undo']
            if command in list_of_modifying_commands:
                modify_list_of_apartments_with_maximum_values(apartments, list_of_apartments_with_maximum_values)
                if not command == 'undo':
                    list_of_operation_results.append(deepcopy(apartments))
        except KeyError:
            print(f"Option {command} is not yet implemented")
        except ValueError as ve:
            print(ve)
        except IndexError:
            print(f"List index out of range")
