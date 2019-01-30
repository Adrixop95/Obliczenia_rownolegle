#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iterator>
#include <mpi.h>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

typedef	vector<int>	vertices;	// sorted
typedef	int			vertex;
vector<vertices>	N;			// neighbors

int moj_nr, p, c;

void BronKerbosh(vertices R, vertices P, vertices X) {
	if (P.empty() and X.empty()) {
		for (vertex r : R) cout << r << " "; // report R as a maximal clique
		cout << endl;
	} else {
		vertices U, V;
		set_union(P.begin(), P.end(), X.begin(), X.end(), back_inserter(U));
		vertex u = U[rand() % U.size()];
		set_difference(P.begin(), P.end(), N[u].begin(), N[u].end(), inserter(V, V.begin()));
		for (vertex v : V) {
			vertices A, B, C, singleton = { v };
			set_union(R.begin(), R.end(), singleton.begin(), singleton.end(), back_inserter(A));
			set_intersection(P.begin(), P.end(), N[v].begin(), N[v].end(), back_inserter(B));
			set_intersection(X.begin(), X.end(), N[v].begin(), N[v].end(), back_inserter(C));
			BronKerbosh(A, B, C);
			remove(P.begin(), P.end(), v);
			auto it = find_if(X.begin(), X.end(), [v](const int &x) { return x > v; });
			X.insert(it, v);
		}
	}
}

void vprint( vector<vertices> x ) {
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x[i].size(); j++) {
			printf("%d, ", x[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

string loadfile( string path ) {
	ifstream myfile( path );
	string output = "";
	string line = "";

	if (myfile.is_open()) {
		cout << "Jest plik" << endl;
		while ( getline(myfile, line) ) {
			output += (line + "\n");
		}
		myfile.close();
	}
	return output;
}

vector< vertices > parse(string text) {
	vector< vertices > output;
	string num = "";
	vector<int> next;
	for (int c = 0; c < text.size(); c++) {
		if (text[c] == ' ') {
			next.push_back(atoi(num.c_str()));
			num = "";
		} else if (text[c] == '\n') {
			next.push_back(atoi(num.c_str()));
			num = "";

			output.push_back(next);
			next.clear();
		} else {
			num += text[c];
		}
	}
	return output;
}

int main( int argc, char *argv[] ) {
	/*
	if (argc > 1) {
		string plik = loadfile( argv[1] );
	}
	*/

	string tekst = loadfile("test.txt");
	N = parse(tekst);

	srand(time(0));
	//N.reserve(5);
	//N.push_back({ 0 });
	//N.push_back({ 0, 2, 3, 4 });
	//N.push_back({ 1, 3 });
	//N.push_back({ 1, 2, 4 });
	//N.push_back({ 1, 3 });
	vprint(N);
	
	MPI_Init(&argc, &argv); // Start oblicze� MPI

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); // Odczytaj numer procesu
	MPI_Comm_size(MPI_COMM_WORLD, &p); // Odczytaj liczb� proceso�w

	if (moj_nr < p) {
		auto start = chrono::high_resolution_clock::now(); //Liczenie czasu start

		BronKerbosh({}, { 0, 1, 2, 3, 4 }, {});
		auto finish = chrono::high_resolution_clock::now(); //Liczenie czasu stop

		chrono::duration<double> elapsed = finish - start; //czas ca�kowity + print
		cout << "Czas: " << elapsed.count() << "s\n";
	}

		MPI_Finalize();
	return 0;
}