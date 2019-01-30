#include <iostream>
#include <mpi.h>
#include <string>
#include <iterator>
#include <chrono>

using namespace std;

string	slowa_kluczowe_python[] =	{
	"and",		"as",		"assert",	"break",	"class",	"continue",	"def",		"del",
	"elif",		"else",		"except",	"exec",		"finally",	"for",		"from",		"global",
	"if",		"import",	"in",		"is",		"lambda",	"not",		"or",		"pass",
	"print",	"raise",	"return",	"try",		"while",	"with",		"yeld" };
int	table_size = 31;
int moj_nr, p, c;

unsigned int hash( const char* s, unsigned int c ) {
	unsigned int x = 0;

	for (unsigned int i = 0; s[i] != 0; ++i) {
		x <<= 3;
		x ^= s[i];
	}

	return (c / x) % 41;
}

unsigned int *hashuj_tablice( unsigned int c ) {
	unsigned int	*nowa_tablica	=	new unsigned int[table_size]();
	for (int k = 0; k < table_size; k++) {
		nowa_tablica[k] = ::hash(slowa_kluczowe_python[k].c_str(), c);
	}
	return nowa_tablica;
}

int main(int argc, char* argv[]) {

	int x;
	/*
	cout << "Podaj liczbe: " << endl;
	cin >> x;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < size(slowa_kluczowe_python); j++) {
			::hash(slowa_kluczowe_python[j].c_str(), x);
		}
	}
	*/

	MPI_Init(&argc, &argv); // Start oblicze� MPI

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // Odczytaj numer procesu
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Odczytaj liczb� proceso�w

	// Pobranie od u�ytkownika liczby c, rozg�aszanie
	//if (moj_nr == 0) {
	//	cout << "Podaj liczbe c: " << endl;
	//	scanf_s("%d", &c);
	//}
	//MPI_Bcast(&c, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (moj_nr < p) {
		auto start = chrono::high_resolution_clock::now(); //Liczenie czasu start

		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < table_size; j++) {
				hashuj_tablice( 1000 );
			}
		}
		auto finish = chrono::high_resolution_clock::now(); //Liczenie czasu stop

		chrono::duration<double> elapsed = finish - start; //czas ca�kowity + print
		cout << "Czas: " << elapsed.count() << "s\n";
	}

	MPI_Finalize();	// Koniec oblicze� MPI
	return 0;
}