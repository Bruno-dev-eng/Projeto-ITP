#include <iostream>
using namespace std;

    class RGB {
        int r;
        int g;
        int b;
    };

    struct Paleta {
        int quantCores;
        RGB cores[100];
        int limites[100];
    };

    Paleta cores = {
        3, {{ 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 }}, { 0, 10, 20 }
    };

int main() {

    return 0;

};
