#include <iostream>
#include <mpi.h>

// Definicja tablicy 2D zgodnie z zadaniem 8000x8000
// Rozmiar Tablicy
const int width = 10;
const int height = 10;
int **arr;

using namespace std;

// Sprawdzenie s¹siadów danego punktu
int live_death( int x, int y ) {
	int count = 0;

	try {
		// Pole po lewej stronie
		if (x > 0) { if (arr[y][x-1] == 1) { count++; } }
		// Pole po prawej stronie
		if (x < width - 2) { if (arr[y][x+1]) { count++; } }
		// Pola powy¿ej
		if (y > 0) {
			// Pole powy¿ej po lewej stronie
			if (x > 0) { if (arr[y-1][x-1] == 1) { count++; } }
			// Pole powy¿ej
			if (arr[y-1][x] == 1) { count++; }
			// Pole powy¿ej po prawej stronie
			if (x < width-2) { if (arr[y-1][x+1]) { count++; } }
		}
		// Pola poni¿ej
		if (y < height - 2) {
			// Pole poni¿ej po lewej stronie
			if (x > 0) { if (arr[y+1][x-1] == 1) { count++; } }
			// Pole poni¿ej
			if (arr[y+1][x] == 1) { count++; }
			// Pole poni¿ej po prawej stronie
			if (x < width - 2) { if (arr[y+1][x+1]) { count++; } }
		}
	} catch ( exception exc ) {

	}

	return count;
}

// Drukowanie tablicy na ekranie komputera
void print_array() {
	for ( int y = 0; y < height; y++ ) {
		for ( int x = 0; x < width; x++ ) {
			cout << arr[y][x];
		}

		cout << endl;
	}
}

// Wykonywanie kroku sztucznego ¿ycia
// Nowa tablica tak aby nie pracowaæ na sta³ej
// Jak masz 0 1 0 a badasz pierwsze [0] 1 0
// to do zmiany to dostaniesz 1 1 0,
// a potem pracujesz na 1 [1] 0 przez co 1 [1] 0 nie umrze
int** step() {

	int **new_arr = new int*[height];

	for ( int y = 0; y < height; y++ ) {
		new_arr[y] = new int[width];

		for (int x = 0; x < width; x++) {
			int ld = live_death(x, y);
			if ( arr[y][x] == 0 && (ld > 0 && ld <=2) ) { new_arr[y][x] = 1; }
			else if ( arr[y][x] == 1 && (ld == 0 || ld > 2) ) { new_arr[y][x] = 0; }
			else { new_arr[y][x] = arr[y][x]; }
		}

	}

	return new_arr;
}

void fill_array(int **arr) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (y == x) { arr[y][x] = 1; }
			else { arr[y][x] = 0; }
		}
	}
}

int main() {
	// Konfiguracja tablicy startowej
	arr = new int*[height];
	for ( int i = 0; i < height; i++ ) arr[i] = new int[width];
	fill_array(arr);

	cout << "Print 1" << endl;
	print_array();
	cout << "Work" << endl;
	arr = step();

	cout << "Print 2" << endl;
	print_array();

	cin.get();
	return 0;
}