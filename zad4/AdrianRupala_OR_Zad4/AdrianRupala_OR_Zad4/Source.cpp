#include <iostream>
#include <string>
#include <iterator>
#include <chrono>
#include <string>
#include <mpi.h>

using namespace std;

int moj_nr, p;

string commands[] = {
	"and", "del", "from", "not", "while",
	"as", "elif", "global", "or", "with",
	"assert", "else", "if", "pass", "yield",
	"break", "except", "import", "print",
	"class", "exec", "in", "rasie",
	"continue", "finally", "is", "return",
	"def", "for", "lambda", "try"
};

unsigned int hash(string command, unsigned int c) {
	int x = 0;

	for (int i = 0; i < size(command); i++) {
		x <<= 3;
		x ^= command[i];
	}
	return int((c / x) % 41);
}

int *hashuj_tablice(string *tablica, int tSize, unsigned int c) {
	int *ret = new int[tSize];
	for (int i = 0; i < tSize; i++) {
		ret[i] = ::hash(tablica[i], c);
	}
	return ret;
}

int count(int *tablica, int tSize, int item) {
	int c = 0;
	for (int i = 0; i < tSize; i++) {
		if (tablica[i] == item) { c += 1; }
	}
	return c;
}

bool sprawdz_unikalnosc(int *tablica, int size) {
	for (int i = int(moj_nr * INT_MAX / p); i < int((moj_nr + 1) * INT_MAX / p); i++) {
		if (count(tablica, size, tablica[i]) != 1) { return false; }
	}
	return true;
}

int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int	commands_size = size(commands);
	if (moj_nr < p) {
		auto start = chrono::high_resolution_clock::now();

		for (int i = int(moj_nr * INT_MAX / p); i < int((moj_nr + 1) * INT_MAX / p); i++) {
			int *hashed = hashuj_tablice(commands, commands_size, i);
			if (sprawdz_unikalnosc(hashed, commands_size)) {
				cout << i << endl;
			}
		}
		auto finish = chrono::high_resolution_clock::now();

		chrono::duration<double> elapsed = finish - start;
		cout << "Czas: " << elapsed.count() << "s\n";
	}

	// 1970821528  - wynik, czas 2584.33 seconds dla 16 rdzeni

	MPI_Finalize();
	return 0;
}