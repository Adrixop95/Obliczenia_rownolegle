#include <iostream>
#include <mpi.h>
#include <chrono>

// Globalne zmienne potrzebne do inicjowania reszty
int moj_nr, p, c; // Moj_nr -> numer procesu, p -> liczba procesów, c -> liczba od urzytkownika
int counter = 0; // Counter -> liczba wyst¹pieñ danej liczby

using namespace std;

// Funkcja z zadania
int f(int i) {
	int i4_huge = 2147483647;
	int j, k, value = i;

	for (j = 1; j <= 5; j++) {
		k = value / 127773;
		value = 16807 * (value - k * 127773) - k * 2836;
		if (value <= 0)
			value = value + i4_huge;
	}

	return value;
}

void sprawdzenie(int c) {
	
	// Sprawdzenie zgodnie z za³o¿eniem f(j) == c dla liczby 2000000000
	for (int j = 1; j < 2000000000; j++) { 
		if (j % (moj_nr+1) == 0) { // if j % (moj_numer+1) = 0 {...}  <- pozielenie na thready
			if (f(j) == c) {
				cout << "Znalazlem! " << f(j) << endl;
				counter++;
			}
		}
	}

	cout << "Liczba wystapien: " << counter << endl;
}


int main(int argc, char* argv[]) {
	
	/*
	int c,
	counter = 0;

	cout << "Podaj C: ";
	cin >> c;
	cin.get();

	auto start = chrono::high_resolution_clock::now();
	sprawdzenie(c);
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Czas: " << elapsed.count() << "s\n";
		
	// Wynik dla i7-8700/16gb ram, liczba c = 1229094172
	// Czas: 121.717s, 
		
	*/
	
	MPI_Init(&argc, &argv); // Start obliczeñ MPI

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // Odczytaj numer procesu
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Odczytaj liczbê procesoów

	// Pobranie od u¿ytkownika liczby c, rozg³aszanie
	if (moj_nr == 0) {
		cout << "Podaj liczbe c: " << endl;
		scanf_s("%d", &c);
	}
	MPI_Bcast(&c, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (moj_nr < p) {		
		auto start = chrono::high_resolution_clock::now(); //Liczenie czasu start
		sprawdzenie(c); // funkcja z zadania 
		auto finish = chrono::high_resolution_clock::now(); //Liczenie czasu stop
		
		chrono::duration<double> elapsed = finish - start; //czas ca³kowity + print
		cout << "Czas: " << elapsed.count() << "s\n";
		
		/*
			Wynik dla i7-8700/16gb ram, liczba c = 1229094172
			2 procesy -> Czas: 123.191s
						 Czas: 63.3737s
		
			4 procesy -> Czas: 123.115s
						 Czas: 33.5154s
						 Czas : 63.5318s
						 Czas : 43.3234s
		
			6 procesów -> Czas: 123.535s
						  Czas: 64.2632s
						  Czas: 28.4757s
						  Czas: 24.247s
						  Czas: 34.3519s
						  Czas: 44.0315s
		*/
	}


	MPI_Finalize();	// Koniec obliczeñ MPI
	return 0;
}