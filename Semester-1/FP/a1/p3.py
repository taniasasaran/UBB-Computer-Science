# Sasaran Tania
# Solve the problem from the third set here
# Problem number 13

def isPrime(number):
    """
    This function checks if a number is prime or not
    """
    if number < 2 or (number > 2 and number % 2 == 0):
        return False
    divisor = 3
    while divisor * divisor <= number:
        if number % divisor == 0:
            return False
        divisor += 2
    return True


def primeDivisorsCounter(number):
    """
    This function counts the prime divisors of a given number
    """
    numberOfDivisors = 0
    if isPrime(number) or number == 1:
        return 1
    if number % 2 == 0:
        numberOfDivisors += 1
    i = 3
    while i <= int(number / 2):
        if number % i == 0 and isPrime(i):
            numberOfDivisors += 1
        i += 2
    return numberOfDivisors


def kthPrimeDivisor(number, counter):
    """
    This function returns the prime number situated on the given position in an array
    that contains divisors of the natural numbers
        counter: the position
        number: the given number
    """
    if number == 1:
        return 1
    if number % 2 == 0 and counter == 1:
        return 2
    if isPrime(number):
        return number
    if number % 2 == 0:
        counter -= 1
    for i in range(3, number, 2):
        if number % i == 0 and isPrime(i):
            counter -= 1
        if counter == 0:
            return i

    return -1


def findPrimeOnPosition(position):
    i = 1
    while position > 0:
        position -= primeDivisorsCounter(i)
        i += 1
    i -= 1
    newPosition = primeDivisorsCounter(i) + position
    return kthPrimeDivisor(i, newPosition)


def main():
    number = int(input("The number you want to check for is: "))
    print("\nThe prime you search for is: ", findPrimeOnPosition(number))


main()
