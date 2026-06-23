#include "Imagem.h"
#include <fstream>

// reutilizar o delete para facilitar em caso de mudança

Imagem::Imagem(int largura, int altura) {

    // Armazena as dimensões recebidas.
    this->largura = largura;
    this->altura = altura;

    // Aloca o vetor de linhas da matriz.
    pixels = new Pixel*[this->altura];

    // Para cada linha, aloca um vetor de pixels.
    for (int linha = 0; linha < this->altura; linha++) {
        pixels[linha] = new Pixel[this->largura];
    }

    // Como Cor possui construtor padrão com valores 0, então os pixels ficam inicialmente pretos.
}

Imagem::~Imagem() {

    // Libera cada linha da matriz.
    for (int linha = 0; linha < this->altura; linha++) {
        delete[] pixels[linha];
    }

    // Libera o vetor principal de ponteiros.
    delete[] pixels;
}

// Retorna a cor do pixel localizado na posição
Pixel Imagem::getPixel(int linha, int coluna) {
    return pixels[linha][coluna];
}

// Define a cor do pixel localizado na posição
void Imagem::setPixel(int linha, int coluna, Pixel cor) {
    pixels[linha][coluna] = cor;
}

// Lê uma imagem no formato PPM (P3).
void Imagem::lerPPM(const std::string& nomeArquivo) {

    // Abre o arquivo para leitura.
    std::ifstream arquivo(nomeArquivo);

    // Se não conseguir abrir o arquivo, encerra o método.
    if (!arquivo.is_open()) {
        return;
    }

    std::string formato;
    int novaLargura;
    int novaAltura;
    int maxValor;

    // Lê o cabeçalho do arquivo PPM.
    arquivo >> formato;       // Deve ser "P3"
    arquivo >> novaLargura >> novaAltura;
    arquivo >> maxValor;      // Geralmente 255

    // Se as dimensões do arquivo forem diferentes das dimensões atuais da imagem, é necessário realocar toda a matriz de pixels.
    if (novaLargura != largura || novaAltura != altura) {

        // Libera a matriz atual.
        for (int linha = 0; linha < altura; linha++) {
            delete[] pixels[linha];
        }

        delete[] pixels;

        // Atualiza as novas dimensões.
        largura = novaLargura;
        altura = novaAltura;

        // Aloca novamente a matriz.
        pixels = new Pixel*[altura];

        for (int linha = 0; linha < altura; linha++) {
            pixels[linha] = new Pixel[largura];
        }
    }

    // Lê todos os pixels da imagem.
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {

            int vermelho;
            int verde;
            int azul;

            // Lê os componentes RGB do pixel.
            arquivo >> vermelho >> verde >> azul;

            // Cria uma cor e armazena na posição correspondente.
            pixels[linha][coluna] = Cor(vermelho, verde, azul);
        }
    }

    // Fecha o arquivo.
    arquivo.close();
}

// Salva a imagem atual em um arquivo PPM (P3).
void Imagem::salvarPPM(const std::string& nomeArquivo) {

    // Abre o arquivo para escrita.
    std::ofstream arquivo(nomeArquivo);

    // Se não conseguir abrir o arquivo, encerra o método.
    if (!arquivo.is_open()) {
        return;
    }

    // Escreve o cabeçalho do formato PPM.
    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    // Percorre toda a matriz de pixels.
    for (int linha = 0; linha < altura; linha++) {
        for (int coluna = 0; coluna < largura; coluna++) {

            // Escreve os valores RGB do pixel.
            arquivo << pixels[linha][coluna].r << " "
                    << pixels[linha][coluna].g << " "
                    << pixels[linha][coluna].b << " ";
        }

        // Quebra de linha ao final de cada linha da imagem.
        arquivo << "\n";
    }

    // Fecha o arquivo.
    arquivo.close();
}
