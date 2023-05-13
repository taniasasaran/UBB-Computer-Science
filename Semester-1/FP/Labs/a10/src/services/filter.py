
def less_than_5(item):
    if item >= 5:
        return False
    return True


def filter_function(list_to_be_filtered, acceptance_function):
    new_list = list()
    for element in list_to_be_filtered:
        if acceptance_function(element):
            new_list.append(element)
    return new_list

