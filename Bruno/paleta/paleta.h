#ifndef PALETA_H
#define PALETA_H

#include <string>
#include <vector>

struct Cor
{
    int r;
    int g;
    int b;
};

class Paleta
{
private:
    std::vector<Cor> cores;

public:
    Paleta();
    Paleta(std::string nomeArquivo);

    void adicionarCor(Cor cor);

    int obterTamanho() const;

    Cor obterCor(int indice) const;
};

#endif
