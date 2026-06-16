#include "Imagem.h"

Imagem::Imagem(int largura, int altura) {
    largura = largura;
    altura = altura;
    pixels = new Pixel*[altura];

    for (int i = 0; i < altura; i++) {
        pixels[i] = new Pixel[largura];
    }
}

imagem::~Imagem() {
    
}