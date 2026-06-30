#ifndef PALETA_H
#define PALETA_H

#include <vector>
#include <string>
#include "Cor.h"

class Paleta {
private:
    std::vector<Cor> cores;

public:
    Paleta();
    Paleta(const std::string& nomeArquivo);

    void adicionarCor(const Cor& cor);
    int obterTamanho() const;
    Cor obterCor(int indice) const;
};

#endif
