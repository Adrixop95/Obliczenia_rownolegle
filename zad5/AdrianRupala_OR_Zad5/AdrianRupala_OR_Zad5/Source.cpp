#include <iostream>
#include <math.h>
#include <mpi.h>
#include <chrono>

using namespace std;

int moj_nr, p; // globalne zmiennie dt. MPI

// z³o¿onoœæ tej funkcji jest kwadratowa, to obliczanie bêdzie trwa³o wiecznoœæ na moim sprzêcie, nie podejmujê siê tego, INT_MAX (32bit) to 2147483647, mo¿na u¿yæ _I64_MAX (64 bit) co daje jeszcze wiêkszy zakres 9223372036854775807
void calculate() {
	for (int x = 0; x <= INT_MAX; x++) { // liczby rzeczywiste x dodatnie od 0 do MAX_INT32 w c++ 2147483647
		if (x % p == moj_nr) { // podzia³ na w¹tki MPI
			for (int y = 0; y <= INT_MAX; y++) { // liczby rzeczywiste y dodatnie od 0 do MAX_INT32 w c++ 2147483647
				if (x - y < 2 && 2 * x + 3 * y < 1 && (0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008) { // warunek z zadania
					cout << "x: " << x << ", y: " << y << endl; // wypisz liczby
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv); // start obliczeñ mpi

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // definiowanie numeru procesu 
	MPI_Comm_size(MPI_COMM_WORLD, &p); // definiowanie liczby procesów

	if (moj_nr < p) { // warunek zawsze sprawdzony, nie jest wymagany
		auto start = chrono::high_resolution_clock::now(); // czas start
		calculate(); // wykonanie funkcji
		auto finish = chrono::high_resolution_clock::now(); // czas stop

		chrono::duration<double> elapsed = finish - start; // obliczenie czasu 
		cout << "Czas:" << elapsed.count() << "s\n"; // wypisanie czasu
	}
	
	MPI_Finalize(); // zakoñczenie obliczeñ mpi
	return 0;
}