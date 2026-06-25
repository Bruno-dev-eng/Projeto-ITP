#include <iostream>
#include <algorithm>
#include "Terreno.h"
#include "Imagem.h"
#include "Paleta.h"
#include "Cor.h"

void gerarTerrenoColorido(int n, double rugosidade, const std::string& nomeArquivo) {
    // 1. Inicializa o terreno usando o seu construtor padrão
    Terreno terreno(n);
    terreno.gerarTerreno(rugosidade);
    
    // Acessa a variável 'tamanho' diretamente da sua classe Terreno
    int tam = terreno.tamanho; 

    // 2. Inicializa a paleta com o arquivo de texto
    Paleta paleta("cores.txt");
    int totalCores = paleta.obterTamanho();

    // Plano B: Se o 'cores.txt' não abrir, define cores básicas na marra
    if (totalCores == 0) {
        paleta.adicionarCor(Cor(0, 0, 128));     // Água
        paleta.adicionarCor(Cor(210, 180, 140)); // Areia
        paleta.adicionarCor(Cor(34, 139, 34));   // Grama
        paleta.adicionarCor(Cor(139, 137, 137)); // Rocha
        paleta.adicionarCor(Cor(255, 255, 255)); // Neve
        totalCores = paleta.obterTamanho();
    }

    // 3. Encontra os limites mínimos e máximos acessando 'altitudes' direto
    double altMin = terreno.altitudes[0][0];
    double altMax = terreno.altitudes[0][0];
    
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            double alt = terreno.altitudes[i][j]; // Acesso direto à sua matriz
            if (alt < altMin) altMin = alt;
            if (alt > altMax) altMax = alt;
        }
    }
    double delta = (altMax - altMin == 0) ? 1.0 : (altMax - altMin);

    // 4. Cria a sua classe Imagem (largura, altura)
    Imagem imagem(tam, tam);

    // 5. Mapeia as altitudes para os pixels da imagem
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            // Normaliza o valor entre 0.0 e 1.0
            double normalizado = (terreno.altitudes[i][j] - altMin) / delta;
            
            // Escolhe o índice da cor baseado na altura
            int indiceCor = static_cast<int>(normalizado * (totalCores - 1));
            indiceCor = std::clamp(indiceCor, 0, totalCores - 1);

            // Pega a cor correspondente e define o pixel usando o seu método setPixel
            Cor corBioma = paleta.obterCor(indiceCor);
            imagem.setPixel(i, j, corBioma); // Seu método original da classe Imagem
        }
    }

    // 6. Salva o arquivo final usando o seu método salvarPPM
    std::cout << "Salvando mapa bioma em " << nomeArquivo << "..." << std::endl;
    imagem.salvarPPM(nomeArquivo);
}

int main() {
    // Configurado de primeira para salvar como teste_mapa.ppm
    gerarTerrenoColorido(8, 80.0, "teste_mapa.ppm");
    std::cout << "Sucesso! Arquivo 'teste_mapa.ppm' gerado." << std::endl;
    return 0;
}

// g++ main.cpp Terreno.cpp Imagem.cpp Paleta.cpp Cor.cpp -o gerador_terreno && ./gerador_terreno