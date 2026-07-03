#include <iostream>
#include <algorithm> 
#include <cmath>     
#include <cstdlib>   
#include "Terreno.h" 
#include "Imagem.h"  
#include "Paleta.h"  
#include "Cor.h"     


void gerarTerrenoColorido(int n, double rugosidade, const std::string& nomeArquivo) {
    Terreno terreno(n);
    terreno.gerarTerreno(rugosidade);
    
    int tam = terreno.tamanho; 

    Paleta paleta("Cores.txt");
    int totalCores = paleta.obterTamanho();

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

    double lux = -1.0; 
    double luy = -1.0;
    double luz = 0.4;
    
    double lu_norm = std::sqrt(lux * lux + luy * luy + luz * luz);
    lux /= lu_norm; luy /= lu_norm; luz /= lu_norm;

    double escalaVertical = 30.0; 

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            
            double normalizado = (terreno.altitudes[i][j] - altMin) / delta;
            
            int indiceCor = static_cast<int>(normalizado * (totalCores - 1));

            indiceCor = std::clamp(indiceCor, 0, totalCores - 1);

            Cor corBase = paleta.obterCor(indiceCor);

            double dx = 0.0; double dy = 0.0;

            if (i > 0 && i < tam - 1) dx = (terreno.altitudes[i + 1][j] - terreno.altitudes[i - 1][j]) * escalaVertical;
            if (j > 0 && j < tam - 1) dy = (terreno.altitudes[i][j + 1] - terreno.altitudes[i][j - 1]) * escalaVertical;

            double nx = -dx; double ny = -dy; double nz = 1.0;
            double n_norm = std::sqrt(nx * nx + ny * ny + nz * nz);
            nx /= n_norm; ny /= n_norm; nz /= n_norm;

            double dot = nx * lux + ny * luy + nz * luz;
            
            double fatorIluminacao = 1.0 + (dot * 0.4);

            double ruidoMicro = ((double)std::rand() / RAND_MAX * 2.0 - 1.0) * 0.07;
            
            if (normalizado < 0.23) { ruidoMicro *= 0.15; fatorIluminacao = 1.0 + (dot * 0.08); }

            double fatorFinal = fatorIluminacao + ruidoMicro;

            int rFinal = std::clamp(static_cast<int>(corBase.r * fatorFinal), 0, 255);
            int gFinal = std::clamp(static_cast<int>(corBase.g * fatorFinal), 0, 255);
            int bFinal = std::clamp(static_cast<int>(corBase.b * fatorFinal), 0, 255);

            imagem.setPixel(i, j, Cor(rFinal, gFinal, bFinal));
        }
    }

    // SALVAMENTO DO ARQUIVO
    std::cout << "Salvando " << nomeArquivo << "..." << std::endl;
    imagem.salvarPPM(nomeArquivo);
}

int main() {
    gerarTerrenoColorido(10, 75.0, "teste_mapa.ppm");
    
    std::cout << "Sucesso! Arquivo 'teste_mapa.ppm' gerado" << std::endl;
    return 0;  
}

//g++ main.cpp Terreno.cpp Imagem.cpp Paleta.cpp Cor.cpp -o gerador_terreno && ./gerador_terreno
