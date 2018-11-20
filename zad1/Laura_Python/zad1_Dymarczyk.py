from mpi4py import MPI
from functions import f

#MPI.Init()
comm = MPI.COMM_WORLD
#import pdb;pdb.set_trace()
size = comm.Get_size()
rank = comm.Get_rank()
n= 2 * (10**7)
c = f(200)

ret = 0
time = MPI.Wtime()

if rank == 0:
    for i in range(1,int(n/4)):
        if f(i)==c:
            ret+=1

if rank==1:
    for i in range(int(n/4), int(2*n/4)):
        if f(i)==c:
            ret+=1

if rank==2:
    for i in range(int(2*n/4), 3*n//4):
        if f(i)==c:
            ret+=1
if rank==3:
    for i in range(3*n//4, n+1):
        if f(i)==c:
            ret+=1

time = MPI.Wtime() - time

#print (ret)
#data = comm.scatter(ret, root=0)
#import pdb;pdb.set_trace()
print('rank', rank, 'has data:', ret)
print('time',time, 'seconds')
#MPI.Finalize()
