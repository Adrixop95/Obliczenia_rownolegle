from mpi4py import MPI
from functions import f

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
n = 2 * (10 ** 8)
c = f(200)

ret = 0
time = MPI.Wtime()

for i in range(rank*n//size+1, (rank+1)*n//size+1):
    if f(i) == c:
        ret += 1

time = MPI.Wtime() - time

print('rank', rank, 'has data:', ret)
print('time', time, 'seconds')
