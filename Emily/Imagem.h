#ifndef IMAGEM_H
#define IMAGEM_H

#include "Cor.h"
#include <string>

using Pixel = Cor;

class Imagem {
public:
    // Número de colunas da imagem.
    int largura;

    // Número de linhas da imagem.
    int altura;

    // Matriz dinâmica de pixels.
    Pixel** pixels;

    // cria uma imagem com as dimensões informadas, aloca a matriz de pixels e inicializa todos os pixels com preto.
    Imagem(int largura, int altura);

    // libera toda a memória alocada para a matriz.
    ~Imagem();

    // Retorna a cor do pixel localizado na posição
    Pixel getPixel(int linha, int coluna);

    // Define a cor do pixel localizado na posição
    void setPixel(int linha, int coluna, Pixel cor);

    // Lê uma imagem PPM (P3) de um arquivo.
    // Se as dimensões forem diferentes das atuais, a matriz deve ser redimensionada.
    void lerPPM(const std::string& nomeArquivo);

    // Salva a imagem atual em um arquivo PPM (P3).
    void salvarPPM(const std::string& nomeArquivo);
};

#endif
