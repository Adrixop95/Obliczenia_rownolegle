from mpi4py import MPI
from math import sin

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

ret = []
time = MPI.Wtime()

i4_huge = 2*(10**5)


for x in range(rank*i4_huge//size, (rank+1)*i4_huge//size):
    for y in range(1, x+2):
        if 2*x+3*y < 1 and (0.2-y)/(1.3-x)-sin(x)/x < -1.1008:
            ret += (x, y)

print('rank', rank, 'has data:', ret)
print('time', time, 'seconds')
