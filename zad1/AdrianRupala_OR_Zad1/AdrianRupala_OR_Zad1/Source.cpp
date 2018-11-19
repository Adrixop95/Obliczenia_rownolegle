#include <iostream>
#include <mpi.h>
#include <chrono>

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

	//int counter = 0;

	// Chyba poprawne sprawdzenie zgodnie z za³o¿eniem f(j) == c dla liczby 2000000000
	for (int j = 1; j < 2000000000; j++) {
		//cout << j << endl;
		//cout << f(j) << endl; //Sprawdzanie czy to dzia³a

		// if j % moj_numer+1 = 0 {...}  <- pozielenie na thready
		if (j % (moj_nr+1) == 0) {
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

	//int moj_nr, p, c; // Moj_nr -> numer procesu, p -> liczba procesów, c -> liczba od urzytkownika
	//int counter = 0; // Counter -> liczba wyst¹pieñ danej liczby

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // Odczytaj numer procesu
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Odczytaj liczbê procesoów


	// Pobranie od u¿ytkownika liczby c, rozg³aszanie (prezewntacja 1)
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
		// Wynik dla i7-8700/16gb ram, liczba c = 1229094172
		// 2 procesy -> Czas: 120.577s
		// 4 procesy -> takie same wyniki, bez sensu
		// 6 procesów -> takie same wyniki, bez sensu		
	}


	MPI_Finalize();	// Koniec obliczeñ MPI
	return 0;
}