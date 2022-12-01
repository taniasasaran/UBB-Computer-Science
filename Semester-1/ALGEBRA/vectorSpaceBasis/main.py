from copy import deepcopy


def find_number_of_bases(dimension):
    """
    This function calculates the number of bases of the vector space Z2^n over Z2, using the formula:

    (q^n−1)(q^n−q)⋯(q^n−q^(n−1)) = [(q^0)*(q^(n-0)-1)]*[q*(q^(n-1)-1)]*...*[[q^(n-1)]*(q^(n-(n-1))-1)]
                                           \________|                                  \_____________|
                                               ||                                            ||
                                              q^n-1                                         q-1
    :param dimension: n, an integer 1<= n <=4
    :return: an integer
    """
    number_of_bases = 1
    for k in range(n):
        number_of_bases = number_of_bases * pow(2, k) * (pow(2, n - k) - 1)
    return number_of_bases


def vector_space_Z2_n_over_Z2(dimension):  # Z2^n
    """
    This function creates the vector space Z2^n over Z2
    :param dimension: n, an integer 1<= n <=4
    :return: a list of lists
    """
    Z2_n_over_Z2 = list()
    for i in [0, 1]:
        if dimension >= 2:
            for j in [0, 1]:
                if dimension >= 3:
                    for k in [0, 1]:
                        if dimension == 4:  # it is specified that n<=4
                            for l in [0, 1]:
                                Z2_n_over_Z2.append([i, j, k, l])
                        else:
                            Z2_n_over_Z2.append([i, j, k])
                else:
                    Z2_n_over_Z2.append([i, j])
        else:
            Z2_n_over_Z2.append([i])
    return Z2_n_over_Z2


def factors_set(dimension):
    """
    This function creates tuples containing integers from the set {-1, 0, 1} which will later represent the coordinates
    of a vector in a certain basis/system_of_generators
    :param dimension: n, an integer 1<= n <=4
    :return: tuples, but not stored in memory
    """
    for i in [-1, 0, 1]:
        if dimension >= 2:
            for j in [-1, 0, 1]:
                if dimension >= 3:
                    for k in [-1, 0, 1]:
                        if dimension == 4:  # it is specified that n<=4
                            for l in [-1, 0, 1]:
                                yield i, j, k, l
                        else:
                            yield i, j, k
                else:
                    yield i, j
        else:
            yield i


def linear_combination(list_of_generators, dimension):
    """
    This function creates the set of linear combinations of vectors of a given list of generators.

    list_of_generators = [u1,u2,...]  - list of lists
    u - list of n="dimension" elements
    k1,k2,k3,k4 = weights, factors_set
    vector[i] = k1*u1[i] + k2*u2[i] + k3*u3[i] + k4*u4[i]
    :param dimension: n, an integer 1<= n <=4
    :param list_of_generators: list of lists
    :return: a set consisting of tuples, each tuple being a vector(including 0) from the linear combination of the
            vectors from the list_of_generators
    """
    linear_combination_set = set()

    if len(list_of_generators[0]) == 1:
        linear_combination_set.add(0)
        linear_combination_set.add(1)
        return linear_combination_set

    for factors in factors_set(len(list_of_generators)):
        vector = [0 for x in range(dimension)]
        for i, factor in enumerate(factors):
            term = [element * factor for element in list_of_generators[i]]
            vector = [vector[j] + term[j] for j in range(dimension)]
        vector = [element % 2 for element in vector]
        linear_combination_set.add(tuple(vector))
    return linear_combination_set


def create_basis(dimension):
    """
    This function creates a basis for the vector space Z2^n, using recursion.
    It also check whether the vectors are 0 or a linear combination of the other vectors in the list. Basically it
    checks if the vectors are linearly independent or not, important requirement for the list to be a basis.
    Otherwise, it chooses another vector.
    When we find a list of independent vectors that has the length equal to the dimension of the space, thus a basis,
    we add it to the list of basis which we will return at the end of the program.
    We start with a vector and search for another different non-zero vector.
    Then, we search for a third vector, linearly independent with the other two. Therefore, it should be found in the
    vector space Z2^n over Z2, but not in the set of linear combinations of the first two vectors.
    :param dimension: n, an integer 1<= n <=4
    :return: a list of lists
    """
    if dimension == 1:
        return [1]
    zero_list = [0 for i in range(dimension)]
    basis = []
    Z2_n_over_n = vector_space_Z2_n_over_Z2(dimension)
    for vector1 in Z2_n_over_n:
        if not vector1 == zero_list:
            if dimension >= 2:
                for vector2 in Z2_n_over_n:
                    if not (vector2 == vector1 or vector2 == zero_list):
                        if dimension >= 3:
                            for vector3 in Z2_n_over_n:
                                if tuple(vector3) not in linear_combination([vector1, vector2], dimension):
                                    if dimension == 4:  # it is specified that n<=4
                                        for vector4 in Z2_n_over_n:
                                            if tuple(vector4) not in linear_combination([vector1, vector2, vector3], dimension):
                                                basis.append([vector1,vector2,vector3,vector4])
                                    else:
                                        basis.append([vector1,vector2,vector3])
                        else:
                            basis.append([vector1,vector2])
            else:
                basis.append([vector1])

    return basis


def start(n, output_file_1):
    if n<=0:
        output_file_1.write("Please provide and integer greater than 0")
    else:
        if n<=4:
            output_file_1.write(f"1. The number of bases of the vector space Z2^{n} over Z2 is {find_number_of_bases(n)} \n"
                                f"2. The vectors of each such basis are:")
            output_file_1.write(str(create_basis(n)))
        elif n>=5:
            output_file_1.write(f"1. The number of bases of the vector space Z2^{n} over Z2 is {find_number_of_bases(n)} \n"
                                f"2. To generate the bases of Z2^n over Z2, provide an integer between 1 and 4")



Input_file_1 = open("input_file_1.txt", "r")
Output_file_1 = open("output_file_1.txt", "w")
n = int(Input_file_1.read(2))   # n will be a number represented on 2 bytes; greater values have astronomically big numbers of basis
start(n, Output_file_1)


Input_file_2 = open("input_file_2.txt", "r")
Output_file_2 = open("output_file_2.txt", "w")
n = int(Input_file_2.read(2))
start(n, Output_file_2)

Input_file_3 = open("input_file_3.txt", "r")
Output_file_3 = open("output_file_3.txt", "w")
n = int(Input_file_3.read(2))
start(n, Output_file_3)

Input_file_4 = open("input_file_4.txt", "r")
Output_file_4 = open("output_file_4.txt", "w")
n = int(Input_file_4.read(2))
start(n, Output_file_4)

Input_file_5 = open("input_file_5.txt", "r")
Output_file_5 = open("output_file_5.txt", "w")
n = int(Input_file_5.read(2))
start(n, Output_file_5)
