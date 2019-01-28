#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iterator>
#include <mpi.h>

using namespace std;

typedef	vector<int>	vertices;	// sorted
typedef	int			vertex;
vector<vertices>	N;			// neighbors


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



int main() {
	srand(time(0));
	N.reserve(5);
	N[0] = { 1 };
	N[1] = { 0, 2, 3, 4 };
	N[2] = { 1, 3 };
	N[3] = { 1, 2, 4 };
	N[4] = { 1, 3 };
	BronKerbosh({}, { 0, 1, 2, 3, 4 }, {});

	cin.get();
	return 0;
}