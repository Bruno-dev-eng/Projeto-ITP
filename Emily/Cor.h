#ifndef COR_H
#define COR_H

#include <string>

class Cor {
public:
    int r;
    int g;
    int b;

    Cor(); // construtor padrão (preto)
    Cor(int vermelho, int verde, int azul); // construtor RGB
    Cor(const std::string& hex); // construtor hexadecimal
};

#endif