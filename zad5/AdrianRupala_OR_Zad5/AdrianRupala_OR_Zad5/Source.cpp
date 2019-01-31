#include <iostream>
#include <math.h>
#include <mpi.h>
#include <chrono>
#include <vector>

using namespace std;

// globalne zmiennie dt. MPI
int moj_nr, p;

// złożoność tej funkcji jest kwadratowa, to obliczanie będzie trwało wieczność na moim sprzęcie, nie podejmuję się tego, INT_MAX (32bit) to 2147483647, można użyć _I64_MAX (64 bit) co daje jeszcze większy zakres 9223372036854775807
/*
void calculate() {
	for (int x = 1; x <= INT_MAX; x++) { // liczby rzeczywiste x dodatnie od 0 do MAX_INT32 w c++ 2147483647
		if (x % p == moj_nr) { // podział na wątki MPI
			//for (int y = 0; y <= INT_MAX; y++) { // liczby rzeczywiste y dodatnie od 0 do MAX_INT32 w c++ 2147483647
			for (int y = 1; y < x + 2; y++){
				if (y - x < 2 && 2 * x + 3 * y < 1 && (0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008) { // warunek z zadania
					cout << "x: " << x << ", y: " << y << endl; // wypisz liczby
				}
			}
		}
	}
}
*/

/*
int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv); // start obliczeń mpi

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // definiowanie numeru procesu 
	MPI_Comm_size(MPI_COMM_WORLD, &p); // definiowanie liczby procesów

	if (moj_nr < p) { // warunek zawsze sprawdzony, nie jest wymagany
		auto start = chrono::high_resolution_clock::now(); // czas start
		calculate(); // wykonanie funkcji
		auto finish = chrono::high_resolution_clock::now(); // czas stop

		chrono::duration<double> elapsed = finish - start; // obliczenie czasu 
		cout << "Czas:" << elapsed.count() << "s\n"; // wypisanie czasu
	}
	
	MPI_Finalize(); // zakończenie obliczeń mpi
	return 0;
}
*/

void vprint(vector<float*> x) {
	for (int i = 1; i < x.size(); i++) {
		if (i % p == moj_nr) {
			cout << x[i][0] << ", " << x[i][1] << endl;
		}
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	vector< float* >	ret;
	int		n			=	100;
	float	accurancy	=	0.0000001;

	ret.push_back(new float[2]{ 0, 0 });

	auto start = chrono::high_resolution_clock::now();
	for ( int i = int(moj_nr * n / p + 1); i < int((moj_nr + 1) * n / p + 1); i++ ) {
		for ( int j = int(moj_nr * n / p + 1); j < int((moj_nr + 1) * n / p + 1); j++ ) {
			float x = accurancy * i;
			float y = accurancy * j;

			if ((0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008) {
				ret.push_back( new float[2]{ x, y } );
			}
		}
	}

	vprint(ret);

	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start; //czas ca�kowity + print
	cout << "Czas: " << elapsed.count() << "s\n";

	MPI_Finalize();
	return 0;
}