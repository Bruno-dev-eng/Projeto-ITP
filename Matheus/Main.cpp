#include <iostream>
#include <algorithm>
#include "Terreno.h"
#include "Imagem.h"
#include "Paleta.h"
#include "Cor.h"

void gerarTerrenoColorido(int n, double rugosidade, const std::string& nomeArquivo) {
    
    Terreno terreno(n);
    terreno.gerarTerreno(rugosidade);
    
    int tam = terreno.tamanho; 

    Paleta paleta("cores.txt");
    int totalCores = paleta.obterTamanho();

    if (totalCores == 0) {
        paleta.adicionarCor(Cor(0, 0, 128));     // Água
        paleta.adicionarCor(Cor(210, 180, 140)); // Areia
        paleta.adicionarCor(Cor(34, 139, 34));   // Grama
        paleta.adicionarCor(Cor(139, 137, 137)); // Rocha
        paleta.adicionarCor(Cor(255, 255, 255)); // Neve
        totalCores = paleta.obterTamanho();
    }

    double altMin = terreno.altitudes[0][0];
    double altMax = terreno.altitudes[0][0];
    
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            double alt = terreno.altitudes[i][j];
            if (alt < altMin) altMin = alt;
            if (alt > altMax) altMax = alt;
        }
    }
    double delta = (altMax - altMin == 0) ? 1.0 : (altMax - altMin);

    Imagem imagem(tam, tam);

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            double normalizado = (terreno.altitudes[i][j] - altMin) / delta;
            
            int indiceCor = static_cast<int>(normalizado * (totalCores - 1));
            indiceCor = std::clamp(indiceCor, 0, totalCores - 1);
          
            Cor corBioma = paleta.obterCor(indiceCor);
            imagem.setPixel(i, j, corBioma); }
    }
  
    std::cout << "Salvando mapa bioma em " << nomeArquivo << "..." << std::endl;
    imagem.salvarPPM(nomeArquivo);
}

int main() {
    gerarTerrenoColorido(8, 80.0, "teste_mapa.ppm");
    std::cout << "Sucesso! Arquivo 'teste_mapa.ppm' gerado." << std::endl;
    return 0;
}

// g++ main.cpp Terreno.cpp Imagem.cpp Paleta.cpp Cor.cpp -o gerador_terreno && ./gerador_terreno
