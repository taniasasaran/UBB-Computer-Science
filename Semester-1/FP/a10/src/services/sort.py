import random
from copy import deepcopy


def is_less_than(first_element, second_element):
    if first_element > second_element:
        return False
    return True


def is_greater_than(first_element, second_element):
    if first_element < second_element:
        return False
    return True


# def gnome_sort(list_to_be_sorted, function):
#     position = 0
#     while position < len(list_to_be_sorted):
#         if position == 0:
#             position = position + 1
#         if not function(list_to_be_sorted[position][0], list_to_be_sorted[position - 1][0]):
#             position = position + 1
#         else:
#             list_to_be_sorted[position], list_to_be_sorted[position - 1] = \
#                 list_to_be_sorted[position - 1], list_to_be_sorted[position]
#             position = position - 1
#     return list_to_be_sorted


def bingo_sort(list_to_be_sorted, comparing_function):
    sorted_list = list()
    if len(list_to_be_sorted) != 0:
        for j in range(len(list_to_be_sorted)):
            pivot = deepcopy(list_to_be_sorted[0])
            pivot_position = 0

            for i in range(len(list_to_be_sorted)):
                if list_to_be_sorted[i][0]:
                    pivot = list_to_be_sorted[i]
                    pivot_position = i
                    break

            for i in range(len(list_to_be_sorted)):
                if not comparing_function(pivot[0], list_to_be_sorted[i][0]) and list_to_be_sorted[i][0] != 0:
                    pivot = deepcopy(list_to_be_sorted[i])
                    pivot_position = deepcopy(i)
            sorted_list.append(deepcopy(pivot))
            list_to_be_sorted[pivot_position][0] = 0
    return sorted_list


# list_to_be_sorted = [[i, "string"] for i in range(4, 10)]
# random.shuffle(list_to_be_sorted)
# print(f"Sequence before: {list_to_be_sorted}")
#
# list_to_be_sorted = gnome_sort(list_to_be_sorted, is_greater_than)  # desc
# print(f"Sorted sequence after applying Gnome Sort : {list_to_be_sorted}")
# random.shuffle(list_to_be_sorted)
#
# list_to_be_sorted = gnome_sort(list_to_be_sorted, is_less_than)  # asc
# print(f"Sorted sequence after applying Gnome Sort : {list_to_be_sorted}")
# random.shuffle(list_to_be_sorted)

