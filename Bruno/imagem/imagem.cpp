#include "imagem.h"

#include <fstream>

// Construtor padrão
Imagem::Imagem()
{
    largura = 0;
    altura = 0;
    pixels = nullptr;
}

// Construtor com dimensões
Imagem::Imagem(int largura, int altura)
{
    this->largura = largura;
    this->altura = altura;

    pixels = new Pixel[largura * altura];

    // Inicializa todos os pixels como preto
    for (int i = 0; i < largura * altura; i++)
    {
        pixels[i] = {0, 0, 0};
    }
}

// Destrutor
Imagem::~Imagem()
{
    delete[] pixels;
}

// Retorna largura
int Imagem::obterLargura() const
{
    return largura;
}

// Retorna altura
int Imagem::obterAltura() const
{
    return altura;
}

// Acesso para escrita
Pixel& Imagem::operator()(int x, int y)
{
    return pixels[y * largura + x];
}

// Acesso para leitura
const Pixel& Imagem::operator()(int x, int y) const
{
    return pixels[y * largura + x];
}

// Salva no formato PPM
bool Imagem::salvarPPM(std::string nomeArquivo) const
{
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return false;
    }

    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            const Pixel& p = (*this)(x, y);

            arquivo
                << p.r << " "
                << p.g << " "
                << p.b << "\n";
        }
    }

    return true;
}

// Lê um arquivo PPM
bool Imagem::lerPPM(std::string nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return false;
    }

    std::string tipo;

    arquivo >> tipo;

    if (tipo != "P3")
    {
        return false;
    }

    int novaLargura;
    int novaAltura;

    arquivo >> novaLargura;
    arquivo >> novaAltura;

    int valorMaximo;

    arquivo >> valorMaximo;

    delete[] pixels;

    largura = novaLargura;
    altura = novaAltura;

    pixels = new Pixel[largura * altura];

    for (int i = 0; i < largura * altura; i++)
    {
        arquivo
            >> pixels[i].r
            >> pixels[i].g
            >> pixels[i].b;
    }

    return true;
}