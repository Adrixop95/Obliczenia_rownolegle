def hash(command, c):
    x = 0
    for i in command:
        x <<= 3
        x ^= ord(i)
    return int((c / x) % 41)


commands = ["and", "del", "from", "not", "while",
            "as", "elif", "global", "or", "with",
            "assert", "else", "if", "pass", "yield",
            "break", "except", "import", "print",
            "class", "exec", "in", "rasie",
            "continue", "finally", "is", "return",
            "def", "for", "lambda", "try"]


def hashuj_tablice(tablica, c):
    ret = []
    for komenda in tablica:
        ret.append(hash(komenda, c))
    return ret


def sprawdz_unikalnosc(zahashowana_tablica):
    for i in zahashowana_tablica:
        if (zahashowana_tablica.count(i) != 1):
            return False
    return True


from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

ret = []
time = MPI.Wtime()

def zadanie_4(komendy, ret):
    i4_huge = 2 * (10 ** 9)
    for i in range(rank * i4_huge // size, (rank + 1) * i4_huge // size):
        zahaszowana = hashuj_tablice(komendy, i)
        if sprawdz_unikalnosc(zahaszowana):
            # print(i)
            ret += i
            return i
    return 0


zadanie_4(commands, ret)

time = MPI.Wtime() - time

print('rank', rank, 'has data:', ret)
print('time', time, 'seconds')
