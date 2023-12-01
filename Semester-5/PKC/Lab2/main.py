# The general method is the following. Suppose you have a system of two congruences
# x = a (mod m)    (two)
# x = b (mod n)
# This is solvable iff gcd(m,n)|a−b. If this is the case, first find, using Euclid's algorithm,
# x,y such that mu + nv = gcd(m,n).
# Multiply by k = (a-b)/gcd(m,n)
# to get m(uk) + n(vk) = a−b,
# and now a solution is x = a−m(uk) = b+n(vk)=A,
# and all solutions are the numbers x = A (mod lcm(m,n))  (one)
# If you have more than two equations, use this method on the first two to reduce (two) to (one),
# so you have an equation less. Repeat.


def gcdEE(a, b):
    """
    This function computes the greatest common divisor of two integers a and b, along with the coefficients x and y
    such that ax + by = gcd(a, b). It is an implementation of the extended Euclidean algorithm.
    :param a: integer
    :param b: integer
    :return: gcd(a, b), x, y from ax + by = gcd(a, b)
    """
    if a == 0:
        return b, 0, 1
    if b == 0:
        return a, 1, 0
    gcd, x1, y1 = gcdEE(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y


def chinese_remainder_theorem(congruence1, congruence2):
    """
    This function computes the solution to a system of two congruences using the Chinese Remainder Theorem.
    :param congruence1: tuple (a1, n1) representing the congruence x = a1 mod n1
    :param congruence2: tuple (a2, n2) representing the congruence x = a2 mod n2
    :return: a congruence (a, n) representing the solution to the system of the two congruences; x = a mod n
    """
    a1, n1 = congruence1
    a2, n2 = congruence2
    gcd, x, y = gcdEE(n1, n2)
    if gcd == 1:
        A = n1 * a2 * x + n2 * a1 * y
        N = n1 * n2
        return A % N, N
    if (a1 - a2) % gcd != 0:
        return None
    lcm = (n1 // gcd) * n2
    k = (a1 - a2) // gcd
    A = a1 - n1 * x * k
    return A % lcm, lcm


def chinese_remainder_theorem_wrapper(congruences):
    """
    This function computes the solution to a system of congruences using the Chinese Remainder Theorem applied for
    two by two congruences.
    :param congruences: list of tuples (ai, ni) representing the congruence x = ai mod ni
    :return: a congruence (a, n) representing the solution to the system of all congruences; x = a mod n
    """
    if len(congruences) == 0:
        return None, None
    if len(congruences) == 1:
        return congruences[0]
    solution = chinese_remainder_theorem(congruences[0], congruences[1])
    if solution is None:
        return None, None
    for congruence in congruences[2::]:
        solution = chinese_remainder_theorem(solution, congruence)
        if solution is None:
            return None, None
    return solution


def tests():
    congruences = [(2, 3), (2, 5), (3, 11)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] == 47

    congruences = [(2, 3), (3, 5), (2, 7)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] == 23

    congruences = [(2, 3), (3, 5), (2, 11)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] == 68

    congruences = [(3, 5), (38, 100), (2, 6)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] == 38

    congruences = [(2, 3), (3, 4), (2, 12), (3, 11)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] is None

    congruences = [(2, 3), (2, 6), (0, 4), (2, 9), (0, 8), (0, 7), (0, 28)]
    solution = chinese_remainder_theorem_wrapper(congruences)
    assert solution[0] == 56


if __name__ == '__main__':
    tests()
