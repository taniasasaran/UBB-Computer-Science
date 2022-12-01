def get_partition_of_set(set):
    """
    This recursive function finds all the partitions of a given set and generates a lis(but does not store it in memory(yield))
    [[1,2,3,...,n]], [[1], [2,3,...,n]], ...
    :param set: in this case, a list of integers
    :return: None
    """
    if len(set) == 1:
        yield [set]
        return None

    first_element = set[0]
    for small_set in get_partition_of_set(set[1:]):
        # insert `first_set` in each of the subpartition's subsets
        for i, subset in enumerate(small_set):
            yield small_set[:i] + [[first_element] + subset] + small_set[i+1:]
        # put `first_set` in its own subset
        yield [[first_element]] + small_set


def add_literals(partition):
    """
    This function adds the letter "a" to each element of each subset of a set
    :param partition: a list of lists of integers
    :return: a list of lists of strings
    """
    partition_str = []
    partition_set = []
    for set in partition:
        set_str = list(map(str, set))
        partition_str.append(set_str)
    for set_str in partition_str:
        new_set = ["a" + s for s in set_str]
        partition_set.append(new_set)
    return str(partition_set)


def generate_graph(partition):
    """
    This function generates the graph of the equivalence relation corresponding a given partition.
    :param partition: a list of lists of integers
    :return: a list of lists of integers
    """
    graph = list()
    for set in partition:
        for element in set:
            for element2 in set:
                if not element2 == element:
                    graph.append((element, element2))
    return sorted(graph)


def find_number_of_partitions(n):
    """
    The method for computing the number of partitions of a set was is called after the mathematician Eric Temple Bell,
    who wrote about this method in the 1930s. Starting with B0 = B1 = 1, the first few Bell numbers are
    1, 1, 2, 5, 15, 52, 203, 877, 4140, ...
    We view the bell computing method as a triangle in which each element is the sum of the previous element and the
    above number of the previous element.
    We use a matrix of (n+1)x(n+1) entries and compute each element with the formula:
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1]
    Also, we copy the n-th element from the n-th line to the first element of the n+1-th line
            bell[i][0] = bell[i - 1][i - 1]
    The number we need will be the value of bell[n][0]
    :param n: integer, the number of elements of a set
    :return: integer, the number of partitions of a set with n elements
    """
    bell = [[0 for i in range(n + 1)] for j in range(n + 1)]
    bell[0][0] = 1   # We know that the number of get_partition_of_set of an empty set is 1
    for i in range(1, n + 1):
        # copy the n-th element from the n-th line to the first element of the n+1-th line
        bell[i][0] = bell[i - 1][i - 1]

        # Compute the values of the rest of elements on line i
        for j in range(1, i + 1):
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1]
    return bell[n][0]


def start(n, output_file):
    list_of_integers_up_to_n = list(range(1,n+1))
    output_file.write(f"1. The number of partitions on a set A with {n} elements is {find_number_of_partitions(n)} \n"
                       f"2. Using the notation deltaA = [(a1, a1),(a2, a2),...,(a{n}, a{n})], the partitions on a set A with "
                       f"{n} elements and their corresponding equivalence relations are:\n")
    for n, p in enumerate(get_partition_of_set(list_of_integers_up_to_n), 1):
        if str(generate_graph(p)) != "[]":
            L = [add_literals(sorted(p))," -> ", "deltaA U ", add_literals(generate_graph(p)), "\n"]
        else:
            L = [add_literals(sorted(p)), " -> ", "deltaA"]
        output_file.writelines(L)


Input_file_1 = open("input_file_1.txt", "r")
Output_file_1 = open("output_file_1.txt", "w")
n = int(Input_file_1.read(1))
start(n, Output_file_1)

Input_file_2 = open("input_file_2.txt", "r")
Output_file_2 = open("output_file_2.txt", "w")
n = int(Input_file_2.read(1))
start(n, Output_file_2)

Input_file_3 = open("input_file_3.txt", "r")
Output_file_3 = open("output_file_3.txt", "w")
n = int(Input_file_3.read(1))
start(n, Output_file_3)

Input_file_4 = open("input_file_4.txt", "r")
Output_file_4 = open("output_file_4.txt", "w")
n = int(Input_file_4.read(1))
start(n, Output_file_4)

Input_file_5 = open("input_file_5.txt", "r")
Output_file_5 = open("output_file_5.txt", "w")
n = int(Input_file_5.read(1))
start(n, Output_file_5)