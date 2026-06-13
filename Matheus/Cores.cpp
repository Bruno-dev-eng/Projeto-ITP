#include <iostream>
#include <fstream>
#include "Cor.h"

class Paleta { private: int* quantidade; public: Paleta(int n); ~Paleta(); };

Paleta::Paleta(int n) { quantidade = new int (n); }

Paleta::~Paleta() { delete quantidade; };

int main() {
    int n;
    std::cin >> n;
    Paleta aPaleta(n);
    std::ifstream arquivo("Cor.hex");
    for (int i = 0; i < n; i++) { Paleta p(i); }

    return 0;
};
