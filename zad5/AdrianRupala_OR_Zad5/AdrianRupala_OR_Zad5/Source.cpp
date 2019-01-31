#include <iostream>
#include <math.h>
#include <mpi.h>
#include <chrono>
#include <vector>

using namespace std;

int moj_nr, p;

void vprint(vector<float*> x) {
	for (int i = 0; i < x.size(); i++) {
		cout << x[i][0] << ", " << x[i][1] << endl;
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &moj_nr); 
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	vector< float* >	ret;
	int		n = 3333333;
	float	accurancy = 0.0000001;

	ret.push_back(new float[2]{ 0, 0 });

	auto start = chrono::high_resolution_clock::now();
	for (int i = int(moj_nr * n / p + 1); i < int((moj_nr + 1) * n / p + 1); i++) {
		for (int j = int(moj_nr * n / p + 1); j < int((moj_nr + 1) * n / p + 1); j++) {
			float x = accurancy * i;
			float y = accurancy * j;

			if ((0.2 - y) / (1.3 - x) - sin(x) / x < -1.1008) {
				ret.push_back(new float[2]{ x, y });
			}
		}
	}

	vprint(ret);

	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;
	cout << "Czas: " << elapsed.count() << "s\n";

	MPI_Finalize();
	return 0;
}