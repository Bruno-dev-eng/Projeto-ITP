#ifndef TERRENO_H
#define TERRENO_H

#include <cmath>

class Terreno {
public:
    int tamanho;        // Dimensão da matriz
    double** altitudes; // Matriz dinâmica de altitudes

    Terreno(int n);
    ~Terreno();

    void gerarTerreno(double rugosidade);
    void etapaDiamond(int x, int y, int metade, double deslocamento);
    void etapaSquare(int x, int y, int metade, double deslocamento);
    bool posicaoValida(int linha, int coluna) const;
};

#endif