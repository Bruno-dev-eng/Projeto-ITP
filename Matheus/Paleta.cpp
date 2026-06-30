#include "Paleta.h"
#include <fstream>

Paleta::Paleta() {
}

Paleta::Paleta(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) { return; }

    std::string linha;

    while (getline(arquivo, linha)) { cores.push_back(Cor(linha)); }
}

void Paleta::adicionarCor(const Cor& cor) { cores.push_back(cor); }

int Paleta::obterTamanho() const { return cores.size(); }

Cor Paleta::obterCor(int indice) const {
    if (indice < 0 || indice >= cores.size()) { return Cor(); }

    return cores[indice];
}
