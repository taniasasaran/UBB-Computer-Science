import math


def fermat():
    n = int(input("Enter the number: "))
    if n % 2 == 0:
        print("The factor is: ", 2)
        return
    b = 20
    t0 = math.floor(math.sqrt(n))
    print("t0 = ", t0)
    if t0 * t0 == n:
        print("The factor is: ", t0)
        return
    for i in range(1, b + 1):
        t = t0 + i
        s2 = t * t - n
        print("i = ", i, " s2 = ", s2)
        if s2 >= 0:
            s = math.floor(math.sqrt(s2))
            if s * s == s2:
                print("s = ", s)
                print("t = ", t)
                print("The factors are: ", t - s, t + s)
                print("YES")
                return
            else:
                print("NO")


fermat()
