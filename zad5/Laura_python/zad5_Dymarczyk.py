from mpi4py import MPI
from math import sin

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

ret = []
time = MPI.Wtime()

x = 0.0000001
y = 0.0000001
x_add = x
y_add = y
i = 0
while x < 1 / 3 and i < 10:
    while y < 1 / 3 and i < 10:
        if (0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008:
            ret += (x, y)
            x, y = 1, 1
            i += 1
            print(x, y)
        y += y_add
    x += x_add

print('rank', rank, 'has data:', ret)
print('time', time, 'seconds')
