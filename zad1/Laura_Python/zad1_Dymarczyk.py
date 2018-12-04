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


# ##2 procesy
# ('rank', 0, 'has data:', 1)
# ('time', 234.84896368370391, 'seconds')
# ('rank', 1, 'has data:', 0)
# ('time', 235.70964319468476, 'seconds')
#
#
# ##4 procesy
# ('rank', 3, 'has data:', 0)
# ('time', 119.61058353353292, 'seconds')
# ('rank', 1, 'has data:', 0)
# ('time', 119.77864979812875, 'seconds')
# ('rank', 0, 'has data:', 1)
# ('time', 119.82884192932397, 'seconds')
# ('rank', 2, 'has data:', 0)
# ('time', 119.82806609151885, 'seconds')
#
#
# ##6 procesow
# ('rank', 0, 'has data:', 1)
# ('time', 117.71170001523569, 'seconds')
# ('rank', 1, 'has data:', 0)
# ('time', 118.1281531045679, 'seconds')
# ('rank', 2, 'has data:', 0)
# ('time', 118.14321058359928, 'seconds')
# ('rank', 5, 'has data:', 0)
# ('time', 118.27372936881147, 'seconds')
# ('rank', 4, 'has data:', 0)
# ('time', 118.34124491387047, 'seconds')
# ('rank', 3, 'has data:', 0)
# ('time', 118.76636147382669, 'seconds')

