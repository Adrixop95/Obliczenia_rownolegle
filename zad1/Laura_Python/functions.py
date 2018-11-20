import time


def f(i):
    i4_huge = 2147483647
    value = i
    for j in range(1, 6):
        k = (value // 127773)
        value = (16807.0 * (value - k * 127773) - k * 2836)
        if value >= i4_huge:
            #print('przed',value)
            value -= i4_huge
           # print('po', value)

    return value


def test(start=0, end=2 * 10 ** 9):
    time_count = time.time()
    for i in range(start, end):
        a = f(i)
    time_count = time.time() - time_count
    print(time_count)


