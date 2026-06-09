#ifndef COR_H
#define COR_H

#include <string>

class Cor {
    int r;
    int g;
    int b;


public:
    Cor(); //construtor padrao (preto)
    Cor(int vermelho, int verde, int azul); //construtor RGB
    Cor(const std::string& hex); //construtor hex

    int getR() const;
    int getG() const;
    int getB() const;
};

#endif