from mpi4py import MPI
from math import sin

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

ret = []
time = MPI.Wtime()

accurancy = 0.0000001

i = 0

n = 3333333

for i in range(rank * n // size + 1, (rank + 1) * n // size + 1):
    for j in range(rank * n // size + 1, (rank + 1) * n // size + 1):
        x, y = accurancy * i, accurancy * j
        if (0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008:
            # print(x, y)
            ret.append((x, y))

time = MPI.Wtime() - time

print('rank', rank, 'has data:', len(ret), '. For example: ', ret[0])
print('time', time, 'seconds')
