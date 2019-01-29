from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()


def tworz_plansze(n):
    ret = []
    for i in range(n):
        wiersz = []
        for j in range(n):
            if i == j or i == n-1-j:
                wiersz.append(1)
            else:
                wiersz.append(0)
        ret.append(wiersz)
    return ret


plansza = tworz_plansze(10)
for i in range(10):
    print (plansza[i])
