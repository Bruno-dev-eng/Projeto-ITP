#ifndef COR_H
#define COR_H
#include <string>;

class Cor {
public:
    int r;
    int g;
    int b;

    Cor();
    Cor(int red, int green, int blue);
    Cor(const std::string &hex);
};

#endif