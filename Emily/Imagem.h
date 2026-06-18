#ifndef IMAGEM_H
#define IMAGEM_H

#include "Cor.h"
#include <string>

using Pixel = Cor;

class Imagem {
public:
    int largura;
    int altura;
    Pixel** pixels;

    Imagem(int largura, int altura);
    ~Imagem();

    Pixel getPixel(int linha, int coluna);
    void setPixel(int linha, int coluna, Pixel cor);

    void lerPPM(const std::string& nomeArquivo);
    void salvarPPM(const std::string& nomeArquivo);
};

#endif