#include <iostream>
#include <mpi.h>
#include <string>
#include <iterator>

using namespace std;

// Funkcja z PDF
unsigned int hash(const char* s, unsigned int c) {
	unsigned int x = 0;

	for (unsigned int i = 0; s[i] != 0; ++i) {
		x <<= 3;
		x ^= s[i];
	}

	return (c / x) % 41;
}

int main() {

	string slowa_kluczowe_python[] = {"and", "as", "assert", "break", "class", "continue", 
		"def", "del", "elif", "else", "except", "exec", "finally", "for", "from", "global", 
		"if", "import", "in", "is", "lambda", "not", "or", "pass", "print", "raise", 
		"return", "try", "while", "with", "yeld"};


	int x;

	cout << "Podaj liczbe: " << endl;
	cin >> x;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < size(slowa_kluczowe_python); j++) {
			::hash(slowa_kluczowe_python[j].c_str(), x);
		}
	}

	return 0;
}