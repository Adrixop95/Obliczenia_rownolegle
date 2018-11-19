

def f(i):
    i4_huge = 2147483647
    value = float(i)
    for j in range(1, 6):
        k = int(float(value /127773))
        value = int(16807.0 * (value - k * 127773) - k * 2836)
        if value<=0:
            value += i4_huge
    return value