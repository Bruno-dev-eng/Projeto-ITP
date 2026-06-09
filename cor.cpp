#include "Cor.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>


Cor::Cor() {
    r = 0;
    g = 0;
    b = 0;
}

// limita os valores de rgb via clamp
Cor::Cor(int vermelho, int verde, int azul) {
    r = std::clamp(vermelho, 0, 255);
    g = std::clamp(verde, 0, 255);
    b = std::clamp(azul, 0, 255);
}

// Verifica se caractere é hexadecimal válido
static bool isHexChar(char c) {
    return std::isxdigit(static_cast<unsigned char>(c));
}

Cor::Cor(const std::string& hex) {
    std::string h = hex;

    // remove '#' se existir
    if (!h.empty() && h[0] == '#') {
        h = h.substr(1);
    }

    // precisa ter 6 caracteres
    if (h.size() != 6) {
        throw std::invalid_argument("Hex deve ter 6 caracteres");
    }

    // converte cada par separadamente
    r = std::stoi(h.substr(0, 2), nullptr, 16);
    g = std::stoi(h.substr(2, 2), nullptr, 16);
    b = std::stoi(h.substr(4, 2), nullptr, 16);
}

int Cor::getR() const {
    return r;
}

int Cor::getG() const {
    return g;
}

int Cor::getB() const {
    return b;
}
