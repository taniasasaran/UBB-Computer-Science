import numpy as np
import math
import matplotlib.pyplot as plt
import random

pi = math.pi


def distance(point1, point2):
    return math.sqrt((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2)


def randomPointOnCircumference(radius):
    angle = random.uniform(0, 2 * pi)
    x = radius * math.sin(angle)
    y = radius * math.cos(angle)
    return [x, y]


def randomPointBetweenEndpoints(point1, point2):
    multiplier = random.uniform(0, 1)
    x = point1[0] + (point2[0] - point1[0]) * multiplier
    y = point1[1] + (point2[1] - point1[1]) * multiplier
    return [x, y]


def sol1(radius, n):
    """Solves Bertrand's paradox approach no. 1"""
    L = math.sqrt(3) * radius
    countGreaterThanL = 0
    for i in range(n):
        point1 = randomPointOnCircumference(radius)
        point2 = randomPointOnCircumference(radius)
        if distance(point1, point2) > L:
            countGreaterThanL += 1
        X = [point1[0], point2[0]]
        Y = [point1[1], point2[1]]
        plt.plot(X, Y)
    plt.show()
    print("The probability is: " + str(countGreaterThanL / n))


def getChordsFromMidpoints(point, r):
    x0, y0 = point
    if y0 == 0:
        x = np.array([x0, x0])
        y = np.array([-np.sqrt(r ** 2 - x ** 2), +np.sqrt(r ** 2 - x ** 2)])
        return x, y
    m = -x0 / y0
    c = y0 - x0 * m
    A, B, C = m ** 2 + 1, 2 * m * c, c ** 2 - r ** 2
    d = np.sqrt(B ** 2 - 4 * A * C)
    x = np.array(((-B + d), (-B - d))) / 2 / A
    y = m * x + c
    return x, y


def sol2(radius, n):
    """Solves Bertrand's paradox approach no. 2"""
    L = math.sqrt(3) * radius
    countGreaterThanL = 0
    for i in range(n):
        point1 = randomPointOnCircumference(radius)
        newPoint = randomPointBetweenEndpoints(point1, [0, 0])
        x, y = getChordsFromMidpoints(newPoint, radius)
        if distance([x[0], y[0]], [x[1], y[1]]) > L:
            countGreaterThanL += 1
        plt.plot(x, y)
    plt.show()
    print("The probability is: " + str(countGreaterThanL / n))


def randomPointInCircle(radius):
    angle = random.uniform(0, 2 * pi)
    dist = np.sqrt(np.random.random()) * radius
    x, y = dist * np.cos(angle), dist * np.sin(angle)
    # x = random.uniform(-radius, radius)
    # y = -math.sqrt(radius ** 2 - x ** 2) + 2*math.sqrt(radius ** 2 - x ** 2) * np.random.random_sample()
    # y = random.uniform(-math.sqrt(radius ** 2 - x ** 2), math.sqrt(radius ** 2 - x ** 2))
    return [x, y]


def sol3(radius, n):
    """Solves Bertrand's paradox approach no. 3"""
    # circle = plt.Circle((0, 0), radius, color="b", fill=False)
    # ax = plt.gca()
    # ax.cla()  # clear things for fresh plot
    # ax.set_xlim((-radius, radius))
    # ax.set_ylim((-radius, radius))
    # ax.add_patch(circle)

    L = math.sqrt(3) * radius
    countGreaterThanL = 0
    for i in range(n):
        point = randomPointInCircle(radius)
        x, y = getChordsFromMidpoints(point, radius)
        if distance([x[0], y[0]], [x[1], y[1]]) > L:
            countGreaterThanL += 1
        plt.plot(x, y)
    plt.show()
    print("The probability is: " + str(countGreaterThanL / n))


# sol1(1, 1000)
# sol2(1, 1000)
sol3(1, 1000)
