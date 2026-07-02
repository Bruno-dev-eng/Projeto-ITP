#ifndef PALETA_H
#define PALETA_H

#include <vector>
#include <string>
#include "Cor.h"

class Paleta {
public:
    std::vector<Cor> cores; // conjunto dinâmico de cores da paleta (índices 0, 1, 2...)

    Paleta(); // construtor padrão (paleta vazia)
    Paleta(const std::string& nomeArquivo); // construtor que carrega as cores de um arquivo

    void adicionarCor(const Cor& cor); // adiciona uma cor ao final da paleta
    int obterTamanho() const; // retorna a quantidade de cores da paleta
    Cor obterCor(int indice) const; // retorna a cor associada ao índice informado
};

#endif