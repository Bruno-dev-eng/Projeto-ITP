#include "Cor.h"
#include <algorithm>
#include <stdexcept>

Cor::Cor() {
    r = 0;
    g = 0;
    b = 0;
}

// limita os valores RGB entre 0 e 255
Cor::Cor(int vermelho, int verde, int azul) {
    r = std::clamp(vermelho, 0, 255);
    g = std::clamp(verde, 0, 255);
    b = std::clamp(azul, 0, 255);
}

Cor::Cor(const std::string& hex) {
    std::string h = hex;

    // remove o caractere '#' caso exista
    if (!h.empty() && h[0] == '#') {
        h = h.substr(1);
    }

    // verifica se o hexadecimal possui 6 caracteres
    if (h.size() != 6) {
        throw std::invalid_argument("Hex deve ter 6 caracteres");
    }

    // converte os dois primeiros caracteres para vermelho
    r = std::stoi(h.substr(0, 2), nullptr, 16);

    // converte os dois caracteres centrais para verde
    g = std::stoi(h.substr(2, 2), nullptr, 16);

    // converte os dois últimos caracteres para azul
    b = std::stoi(h.substr(4, 2), nullptr, 16);
}