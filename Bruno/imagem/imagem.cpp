#include "imagem.h"
#include <fstream>
#include <iostream>

// Construtor padrão limpo
Imagem::Imagem()
{
    largura = 0;
    altura = 0;
    pixels = nullptr;
}

// Construtor que aloca o vetorzão de pixels
Imagem::Imagem(int largura, int altura)
{
    this->largura = largura;
    this->altura = altura;

    // Aloca tudo em um vetor linear pra ficar mais fácil
    pixels = new Pixel[largura * altura];

    // Loop simples pra pintar tudo de preto (padrão)
    for (int i = 0; i < largura * altura; i++)
    {
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
    }
}

// Destrutor pra não dar memory leak
Imagem::~Imagem()
{
    if (pixels != nullptr) 
    {
        delete[] pixels;
    }
}

int Imagem::obterLargura() const
{
    return largura;
}

int Imagem::obterAltura() const
{
    return altura;
}

// Operador pra acessar pixel como se fosse matriz: img(x, y)
Pixel& Imagem::operator()(int x, int y)
{
    // Conta básica pra achar a posição no vetor linear
    int indice = y * largura + x;
    return pixels[indice];
}

// Versão constante do operador (pra leitura)
const Pixel& Imagem::operator()(int x, int y) const
{
    int indice = y * largura + x;
    return pixels[indice];
}

// Salva a imagem no formato PPM clássico
bool Imagem::salvarPPM(std::string nomeArquivo) const
{
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return false; // Se não conseguiu abrir o arquivo, já era
    }

    // Cabeçalho do PPM
    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    // Varre a imagem e joga os valores no arquivo separados por espaço
    for (int y = 0; y < altura; y++)
    {
        for (int x = 0; x < largura; x++)
        {
            int idx = y * largura + x;
            arquivo << pixels[idx].r << " "
                    << pixels[idx].g << " "
                    << pixels[idx].b << "\n";
        }
    }

    arquivo.close();
    return true;
}

// Abre e lê o arquivo PPM
bool Imagem::lerPPM(std::string nomeArquivo)
{
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return false;
    }

    std::string tipo;
    arquivo >> tipo;

    // Se não for P3, o formato tá errado
    if (tipo != "P3")
    {
        return false;
    }

    int novaLargura, novaAltura, valorMaximo;
    arquivo >> novaLargura >> novaAltura >> valorMaximo;

    // Se já tinha imagem aqui, limpa a memória antes de reallocar
    if (pixels != nullptr)
    {
        delete[] pixels;
    }

    largura = novaLargura;
    altura = novaAltura;
    pixels = new Pixel[largura * altura];

    // Joga os números direto do arquivo para os pixels
    for (int i = 0; i < largura * altura; i++)
    {
        arquivo >> pixels[i].r >> pixels[i].g >> pixels[i].b;
    }

    arquivo.close();
    return true;
}