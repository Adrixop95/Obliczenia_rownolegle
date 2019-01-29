from mpi4py import MPI
import copy

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

#lista1 = [1, 2, 3, 4, 5]
#lista2 = lista1[:]


def krok(plansza, n):
    kopia = copy.deepcopy(plansza)
    for i in range(n):
        for j in range(n):
            komorka = plansza[i][j]
            if komorka:
                pass #TODO funkcja zliczająca sąsiadów


plansza = tworz_plansze(10)
for i in range(10):
    print (plansza[i])
