# x = a1 mod n1
# x = a2 mod n2
# ...
# x = ak mod nk
# gcd(ni, nj) = 1 for all i != j
# implement chinese remainder theorem function for solving system of congruences

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


def isprime(num):
    """
    This function checks if a number is prime or not
    :param num: integer number
    :return: True if it's prime, False otherwise
    """
    if num == 2 or num == 3:
        return True
    if num % 2 == 0 or num < 2:
        return False
    for n in range(3, int(num ** 0.5) + 1, 2):
        if num % n == 0:
            return False
    return True


def split_prime_factors(n):
    # split n into prime factors
    # return list of tuples (prime factor, exponent)
    if isprime(n):
        return [(n, 1)]
    factors = []
    for i in range(2, n // 2 + 1):
        if n % i == 0 and isprime(i):
            exponent = 0
            while n % i == 0:
                exponent += 1
                n //= i
            factors.append((i, exponent))
    return factors


def inverse(N, n):
    for i in range(n):
        if (N * i) % n == 1:
            return i


def check_coprime(congruences):
    for i in range(len(congruences)):
        for j in range(i + 1, len(congruences)):
            if gcdEE(congruences[i][1], congruences[j][1])[0] != 1:
                return False
    return True


# Repeating this, we can assume m, n are prime powers. If we haven't checked compatibility yet, we can do at
# this point as it will be quite straightforward. Assuming they are, if we have a congruence condition modulo pm, we
# can eliminate any other congruence condition modulo pn for any n<m
def merge_congruences(congruence1, congruence2):
    lcm = (congruence1[1] * congruence2[1]) // gcdEE(congruence1[1], congruence2[1])[0]
    split_lcm = split_prime_factors(lcm)
    new_congruences = []
    for pair in split_lcm:
        factor = pow(pair[0], pair[1])
        if congruence1[1] % factor == 0:
            new_congruences.append([congruence1[0] % factor, factor])
        if congruence2[1] % factor == 0:
            new_congruences.append([congruence2[0] % factor, factor])
    return new_congruences


def merge_all_congruences(congruences):
    if check_coprime(congruences):
        return congruences
    if len(congruences) == 1:
        return congruences[0]
    new_congruences = []
    for i in range(0, len(congruences) - 1, 2):
        merge = merge_congruences(congruences[i], congruences[i + 1])
        for congruence in merge:
            if congruence not in new_congruences:
                new_congruences.append(congruence)
    if len(congruences) % 2 == 1:
        new_congruences.append(congruences[-1])
    return merge_all_congruences(new_congruences)


def chinese_remainder_theorem(congruences):
    congruences = merge_all_congruences(congruences)
    N = 1
    for congruence in congruences:
        N *= congruence[1]
    solution = 0
    for congruence in congruences:
        ai, ni = congruence
        Ni = N // ni
        Ki = inverse(Ni, ni)
        solution += ai * Ni * Ki
    return solution % N


congruences = [[18, 100], [6, 56], [6, 7]]
print(chinese_remainder_theorem(congruences))

# congruences = [(2, 3), (2, 6), (0, 4), (2, 9), (0, 8), (0, 7), (0, 28)]
# print(chinese_remainder_theorem(congruences))
