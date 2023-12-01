import time
from random import randrange


def gcdE(a, b):
    """
    This function implements the classic algorithm of Euclid
    :param a: integer number
    :param b: integer number
    :return: gcd(a,b), also integer OR "inf" if both a and b are 0
    """
    if a == 0 and b == 0:
        return "inf"
    if a == 0:
        return b
    return gcdE(b % a, a)


def gcdEE(a, b):
    """
    This function implements the extended Euclidean algorithm. Besides gcd, it also computes the integer coefficients
    x and y of the Bezout's identity: ax+by=gcd(a,b)
    :param a: integer number
    :param b: integer number
    :return: gcd(a,b), x, y, all integers OR "inf","inf","inf" if both a and b are 0
    """
    if a == 0 and b == 0:
        return "inf", "inf", "inf"
    if a == 0:
        return b, 0, 1
    gcd, x1, y1 = gcdEE(b % a, a)
    x = y1 - (b // a) * x1
    y = x1
    return gcd, x, y


def gcd(a, b):
    """
    This function implements a basic gcd algorithm: the one in which we verify each integer from 2 to min(a,b) to see if
    it's a divisor, saving the greatest divisor in a variable every time we find a divisor
    :param a: integer number
    :param b: integer number
    :return: gcd(a,b), also integer OR "inf" if both a and b are 0
    """
    if a == 0 and b == 0:
        return "inf"
    if a == 0:
        return b
    if b == 0:
        return a
    gcd = 1
    for i in range(2, min(a, b) + 1):
        if a % i == 0 and b % i == 0:
            gcd = i
    return gcd


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


def gcdPrimes(a, b):
    """
    This function implements an algorithm that uses primes to check what are the common primes and at what power.
    It goes through all the numbers from 2 to min(a,b), checking if they are prime and then divides a and b to that
    number, while they are divisible by it, multiplying the gcd at the same time
    :param a: integer number
    :param b: integer number
    :return: gcd(a,b), also integer OR "inf" if both a and b are 0
    """
    if a == 0 and b == 0:
        return "inf"
    if a == 0:
        return b
    if b == 0:
        return a
    gcd = 1
    while a % 2 == 0 and b % 2 == 0:
        gcd = gcd * 2
        a = a // 2
        b = b // 2
    for p in range(3, min(a, b) + 1, 2):
        if isprime(p):
            while a % p == 0 and b % p == 0:
                gcd = gcd * p
                a = a // p
                b = b // p
    return gcd


def gcdPrimesEnhanced(a, b, primes):
    """
    This function behaves exactly like gcdPrimes, but it receives a list of primes from 2 to min(a,b)
    :param a: integer number
    :param b: integer number
    :param primes: list of integer prime numbers
    :return: gcd(a,b), also integer OR "inf" if both a and b are 0
    """
    if a == 0 and b == 0:
        return "inf"
    if a == 0:
        return b
    if b == 0:
        return a
    gcd = 1
    for p in primes:
        while a % p == 0 and b % p == 0:
            gcd = gcd * p
            a = a // p
            b = b // p
    return gcd


def main():
    """
    Main function which calls all the above gcds
    It retains a list with the sum of seconds * multiplier it takes each algorithm to compute the gcd
    for each of the 10 pairs of randomly generated numbers
    Firstly, a and b are hardcoded to have veeeery big values, then they are randomly generated from the range 0-999999
    :return: None
    """
    multiplier = pow(10, 6)
    num_algorithms = 5
    times = [0 for _ in range(num_algorithms)]
    t0 = time.time()
    a, b = 123456789987654328, 64732642736478126773722
    print("gcdE(", a, ",", b, ") = ", gcdE(a, b))
    t1 = time.time()
    print((t1 - t0) * multiplier)
    for i in range(1, 11):
        print("\n")
        print("Iteration ", i)
        a, b = randrange(0, 1000000), randrange(0, 1000000)
        print("a=", a, "   b=", b)
        t1 = time.time()
        print("gcdE(", a, ",", b, ") = ", gcdE(a, b))
        t2 = time.time()
        print((t2 - t1) * multiplier)
        times[0] += (t2 - t1) * multiplier
        g, x, y = gcdEE(a, b)
        print("gcdEE(", a, ",", b, ") = ", g)
        t3 = time.time()
        print((t3 - t2) * multiplier)
        times[1] += (t3 - t2) * multiplier
        print("gcd(", a, ",", b, ") = ", gcd(a, b))
        t4 = time.time()
        print((t4 - t3) * multiplier)
        times[2] += (t4 - t3) * multiplier
        print("gcdPrimes(", a, ",", b, ") = ", gcdPrimes(a, b))
        t5 = time.time()
        print((t5 - t4) * multiplier)
        times[3] += (t5 - t4) * multiplier
        primes = [2]
        for p in range(3, min(a, b) + 1, 2):
            if isprime(p):
                primes.append(p)
        t5 = time.time()
        print("gcdPrimesEnhanced(", a, ",", b, ") = ", gcdPrimesEnhanced(a, b, primes))
        t6 = time.time()
        print((t6 - t5) * multiplier)
        times[4] += (t6 - t5) * multiplier
    for i in range(num_algorithms):
        times[i] = times[i] / 10
    print("\ngcdE: ", times[0], ", gcdEE: ", times[1], ", gcd: ", times[2], ", gcdPrimes: ", times[3],
          ", gcdPrimesEnhanced: ", times[4])


main()
print("\nEdge cases: ")
print("gcdE(0, 0)=", gcdE(0, 0))
print("gcdEE(0, 0)=", gcdEE(0, 0)[0])
print("gcd(0, 0)=", gcd(0, 0))
print("gcdPrimes(0, 0)=", gcdPrimes(0, 0))
print("gcdPrimesEnhanced(0, 0)=", gcdPrimesEnhanced(0, 0, [2, 3, 5, 7]))
print("gcdPrimes(81, 0)=", gcdPrimes(81, 0))
print("gcdPrimes(0, 3232)=", gcdPrimes(0, 3232))
