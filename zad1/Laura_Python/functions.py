import time
import numpy as np


def f(i):
    i4_huge = 2147483647
    value = float(i)
    for j in range(1, 6):
        k = int(float(value / 127773))
        value = int(16807.0 * (value - k * 127773) - k * 2836)
        if value <= 0:
            value += i4_huge
    return value

FUNNY = 2 ** 32 - 1

def f2(i):
    i4_huge = 2147483647
    value = i%FUNNY
    for j in range(1, 6):
        k = (value // 127773)
        value = (16807.0 * (value - k * 127773) - k * 2836)
        if value >= i4_huge:
            #print('przed',value)
            value -= i4_huge
           # print('po', value)

    return value


#czas 13.87
def test(start=0, end=2 * 10 ** 9):
    time_count = time.time()
    for i in range(start, end):
        a = f(i)
    time_count = time.time() - time_count
    print(time_count)


#czas
def test_2(start=0, end=2 * 10 ** 9):
    time_count = time.time()
    for i in range(start, end):
        a = f2(i)
    time_count = time.time() - time_count
    print(time_count)


def test2(start=0, end=2 * 10 ** 3):
    time_count = time.time()
    for i in range(start, end):
        if f(i)!=f2(i):
            print (i,"bad")
    time_count = time.time() - time_count
    print(time_count)

