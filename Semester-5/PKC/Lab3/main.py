import random


def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)


def lcm(a, b):
    return a // gcd(a, b) * b


def lcm_list(list):
    LCM = list[0]
    for i in range(1, len(list)):
        LCM = lcm(LCM, list[i])
    return LCM


def pollard(n, bound):
    k = lcm_list(range(1, bound + 1))
    a = random.randint(1, n)
    a = pow(a, k, n)
    d = gcd(a - 1, n)
    if 1 < d < n:
        return d
    else:
        return "Failure"


if __name__ == '__main__':
    n = int(input("Enter the number: "))
    B = 100
    bound = int(input("Enter the bound: "))
    while True:
        result = pollard(n, bound)
        if result != "Failure":
            print("The factor is: ", result)
            break
        else:
            bound = int(input("Enter another bound: "))
            if bound == 0:
                print(result)
                break

# 1241143  13  ==  547
# 1403  8  ==  61
