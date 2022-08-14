# Sasaran Tania
# Solve the problem from the first set here
# Problem number 2

def isPrime(number):
    """
    This function checks if a number is prime or not and returns True or False
    number: a number greater than 2
    """
    if number <= 3:
        return True
    if number % 2 == 0:
        return False
    divisor = 2
    while divisor * divisor <= number:
        if number % divisor == 0:
            return False
        divisor += 1
    return True


def findTwoPrimesSumIsNumber(number):
    """
    This function finds two prime numbers such that their sum is the chosen number
    firstPrime and secondPrime: the prime numbers that have this property
    notFound: checks if the function found the two prime numbers or not
    """
    notFound = 1
    firstPrime = -1
    secondPrime = -1
    for i in range(2, int(number / 2), 1):
        if notFound == 1:
            if isPrime(i) and isPrime(number - i):
                notFound = 0
                firstPrime = i
                secondPrime = number - i
    print("The prime numbers are ", firstPrime, " and ", secondPrime)


def start():
    number = int(input("The number you want to check for is: "))
    if number % 2 == 1:
        print("Please chose an even number!")
    else:
        findTwoPrimesSumIsNumber(number)


start()
