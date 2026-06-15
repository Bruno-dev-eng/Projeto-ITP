#include <algorithm>
#include <stdexcept>
#include "Cor.h"

Cor::Cor() {
    r = 0;
    g = 0;
    b = 0;
}

Cor::Cor(int vermelho, int verde, int azul) {
    r = std::clamp(vermelho, 0, 255);
    g = std::clamp(verde, 0, 255);
    b = std::clamp(azul, 0, 255);
}

Cor::Cor(const std::string &hex) {

    std::string h = hex;

    if (!h.empty() && h[0] == '#') {
        h = h.substr(1);
    }

    if (h.size() != 6) {
        throw std::invalid_argument("Hex deve possuir 6 caracteres legíveis para a operação (RRGGBB)");
    }

    r = std::stoi(h.substr(0, 2), nullptr, 16);
    g = std::stoi(h.substr(2, 2), nullptr, 16);
    b = std::stoi(h.substr(4, 2), nullptr, 16);
}