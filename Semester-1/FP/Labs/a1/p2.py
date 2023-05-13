# Sasaran Tania
# Solve the problem from the second set here
# Problem number 9

def productOfAllTheProperFactors(number):
    """
    This function finds the product of all the proper factors of a number
    product: the number returned
    i: an index going from 2 to the square root of the chosen number
    """
    product = 1
    i = 2
    while i * i < number:
        if number % i == 0:
            product = product * i * int(number / i)
        i += 1
        if i * i == number:
            product = product * i
    print("The product of all the proper factors of the chosen number is: ", product)


def start():
    number = int(input("The number you want to check for is: "))
    productOfAllTheProperFactors(number)


start()
