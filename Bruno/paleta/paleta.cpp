#include "paleta.h"

#include <fstream>
#include <string>

Paleta::Paleta()
{
}

Paleta::Paleta(std::string nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return;
    }

    std::string linha;

    while (std::getline(arquivo, linha))
    {
        if (linha.size() != 7 || linha[0] != '#')
        {
            continue;
        }

        Cor cor;

        cor.r = std::stoi(linha.substr(1, 2), nullptr, 16);
        cor.g = std::stoi(linha.substr(3, 2), nullptr, 16);
        cor.b = std::stoi(linha.substr(5, 2), nullptr, 16);

        cores.push_back(cor);
    }
}

void Paleta::adicionarCor(Cor cor)
{
    cores.push_back(cor);
}

int Paleta::obterTamanho() const
{
    return cores.size();
}

Cor Paleta::obterCor(int indice) const
{
    if (indice < 0 || indice >= cores.size())
    {
        return Cor{0,0,0};
    }

    return cores[indice];
}
