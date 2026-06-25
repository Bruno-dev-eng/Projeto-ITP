#ifndef IMAGEM_H
#define IMAGEM_H

#include <string>

// Representa um pixel RGB
struct Pixel
{
    int r;
    int g;
    int b;
};

class Imagem
{
private:
    int largura;
    int altura;

    // Vetor que armazenará todos os pixels da imagem
    Pixel* pixels;

public:
    // Cria uma imagem vazia (0x0)
    Imagem();

    // Cria uma imagem com largura e altura definidas
    Imagem(int largura, int altura);

    // Libera a memória alocada
    ~Imagem();

    // Retorna largura da imagem
    int obterLargura() const;

    // Retorna altura da imagem
    int obterAltura() const;

    // Permite modificar um pixel
    Pixel& operator()(int x, int y);

    // Permite consultar um pixel
    const Pixel& operator()(int x, int y) const;

    // Lê um arquivo PPM
    bool lerPPM(std::string nomeArquivo);

    // Salva um arquivo PPM
    bool salvarPPM(std::string nomeArquivo) const;
};

#endif