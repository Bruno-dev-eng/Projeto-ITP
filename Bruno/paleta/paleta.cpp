#include "paleta.h"
#include <fstream>
#include <string>
#include <iostream>

// Construtor padrão que não faz nada
Paleta::Paleta()
{
}

// Função auxiliar simples para converter um caractere hex para inteiro.
// Evita usar funções prontas e complexas como std::stoi com ponteiros nulos.
int hexParaInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

// Construtor que lê as cores do arquivo .hex
Paleta::Paleta(std::string nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return; // Arquivo não existe, deixa a paleta vazia
    }

    std::string linha;

    // Lê linha por linha do arquivo
    while (std::getline(arquivo, linha))
    {
        // Validação simples: tem que ter o '#' e mais 6 caracteres do hex
        if (linha.size() < 7 || linha[0] != '#')
        {
            continue; 
        }

        Cor cor;

        // Pega os pares de caracteres e converte manualmente (R, G, B)
        // Ex: #71abd8 -> 7 e 1 pro Vermelho
        cor.r = hexParaInt(linha[1]) * 16 + hexParaInt(linha[2]);
        cor.g = hexParaInt(linha[3]) * 16 + hexParaInt(linha[4]);
        cor.b = hexParaInt(linha[5]) * 16 + hexParaInt(linha[6]);

        cores.push_back(cor);
    }

    arquivo.close();
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
    // Validação de segurança básica pra não estourar o vector
    if (indice < 0 || indice >= (int)cores.size())
    {
        Cor preto = {0, 0, 0};
        return preto;
    }

    return cores[indice];
}