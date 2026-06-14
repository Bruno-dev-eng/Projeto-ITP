#include "Paleta.h"
#include <fstream>

Paleta::Paleta() {
}

Paleta::Paleta(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    // caso o arquivo não exista, a paleta permanece vazia
    if (!arquivo.is_open()) {
        return;
    }

    std::string linha; // armazena temporariamente cada linha do arquivo

    while (getline(arquivo, linha)) { // lê uma linha por vez até chegar ao final do arquivo
        cores.push_back(Cor(linha)); // cria uma cor a partir do hexadecimal lido e a adiciona à paleta
    }
}

void Paleta::adicionarCor(const Cor& cor) {
    cores.push_back(cor); // adiciona a cor ao final do vetor, ocupando o próximo índice disponível
}

int Paleta::obterTamanho() const {
    return cores.size(); // obtém a quantidade de cores da paleta através da quantidade de elementos armazenados no vetor
}

Cor Paleta::obterCor(int indice) const {
    // retorna uma cor padrão (preto) caso o índice informado seja inválido
    if (indice < 0 || indice >= cores.size()) {
        return Cor();
    }

    return cores[indice]; // retorna a cor armazenada no índice informado
}