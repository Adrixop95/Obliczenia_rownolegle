def hash(command, c):
    x = 0
    for i in command:
        x <<= 3
        x ^= ord(i)
    return int((c/x)%41)


commands = ["and", "del", "from", "not", "while",
            "as", "elif", "global", "or", "with",
            "assert", "else", "if", "pass", "yield",
            "break", "except", "import", "print",
            "class", "exec", "in", "rasie",
            "continue", "finally", "is", "return",
            "def", "for", "lambda", "try"]

def hashuj_tablice(tablica, c):
    ret=[]
    for komenda in tablica:
        ret.append(hash(komenda, c))
    return ret


def sprawdz_unikalnosc(zahashowana_tablica):
    for i in zahashowana_tablica:
        if (zahashowana_tablica.count(i)!=1):
            return False
    return True

def zadanie_4(komendy, zakres_do, zakres_od=0):
    for i in range(zakres_od, zakres_do+1):
        zahaszowana = hashuj_tablice(commands, i)
        if sprawdz_unikalnosc(zahaszowana):
            return c
    return 0
        
    
print(zadanie_4(commands, 10**11, int(9.9999*(10**10))))
