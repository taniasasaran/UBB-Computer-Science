import math


def pollard():
    n = int(input("Enter the number: "))
    if n % 2 == 0:
        print("The factor is: ", 2)
        return
    b = 20
    f = lambda y: y * y + 1
    x = [0 for _ in range(b + 1)]
    x[0] = 2
    j = 1
    while True:
        x[j] = f(x[j - 1]) % n
        print("x[", j, "] = ", x[j])
        if j % 2 == 0:
            d = math.gcd(abs(x[j] - x[j//2]), n)
            print(f"(|x{j}-x{j//2}|,n)={d}")
            if 1 < d < n:
                print("The factors are: ", d, n // d)
                return
        j += 1


pollard()
