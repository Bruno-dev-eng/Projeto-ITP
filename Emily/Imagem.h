#ifndef IMAGEM_H
#define IMAGEM_H

#include "Cor.h"

using Pixel = Cor;

class Imagem {
    public:
        int largura;
        int altura;
        Pixel** pixels;

        Imagem(int largura, int altura);
        ~Imagem();
}

#endif