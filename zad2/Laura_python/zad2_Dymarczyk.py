from mpi4py import MPI
import copy


comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

time = MPI.Wtime()

def tworz_plansze(n):
    ret = []
    for i in range(n):
        wiersz = []
        for j in range(n):
            if i == j or i == n - 1 - j:
                wiersz.append(1)
            else:
                wiersz.append(0)
        ret.append(wiersz)
    return ret


def ile_sasiadow(plansza, x, y, n):
    suma = 0
    if x > 0 and y > 0:
     suma += plansza[x - 1][y - 1]
    if x > 0:
     suma += plansza[x - 1][y]
    if x > 0 and y < n - 1:
     suma += plansza[x - 1][y + 1]
    if x and y > 0:
     suma += plansza[x][y - 1]
    if x < n - 1 and y > 0:
     suma += plansza[x + 1][y - 1]
    if x < n - 1:
     suma += plansza[x + 1][y]
    if x < n - 1 and y < n - 1:
     suma += plansza[x + 1][y + 1]
    if y < n - 1:
     suma += plansza[x][y + 1]
    return suma


def krok(plansza, n):
    kopia = copy.deepcopy(plansza)
    for i in range(n):
     for j in range(rank*n//size, (rank+1)*n//size):
         if ile_sasiadow(kopia, i, j, n) in [2, 1]:
             plansza[i][j] = 1
         else:
             plansza[i][j] = 0
    return plansza

def generuj_string(plansza, n):
    ret = ""
    for i in range(n):
        for j in range(n):
            ret += str(plansza[i][j])
        ret += "\n"
    return ret


def zadanie_2(n, k):
    """
    Rozwiazanie zadania 2
    :param n: wymiar macierzy
    :param k: liczba krokow
    wynik zapisany do pliku
    """
    plansza = tworz_plansze(n)
    for i in range(k):
        plansza = krok(plansza, n)
    plik = open('wynik_zadania2', 'w')
    plik.write(generuj_string(plansza, n))
    plik.close()
    return plansza


plansza = zadanie_2(8000, 400)

time = MPI.Wtime() - time

print('rank', rank, ' has time: ', time, 'seconds')
