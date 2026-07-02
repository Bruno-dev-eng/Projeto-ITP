#include <iostream>
#include <algorithm> 
#include <cmath>     
#include <cstdlib>   
#include "Terreno.h" 
#include "Imagem.h"  
#include "Paleta.h"  
#include "Cor.h"     


void gerarTerrenoColorido(int n, double rugosidade, const std::string& nomeArquivo) {
    // GERAÇÃO DO TERRENO BRUTO
    // Inicializa o terreno passando a potência 'n'. 
    Terreno terreno(n);
    // Executa o algoritmo que preenche a matriz 'terreno.altitudes' com valores baseados na rugosidade fornecida.
    terreno.gerarTerreno(rugosidade);
    
    // Armazena o tamanho linear da matriz quadrada 
    int tam = terreno.tamanho; 

    // CARREGAMENTO DA PALETA DE CORES
    // Abre o arquivo de texto que contém a lista de cores RGB que representarão os biomas (água, areia, floresta, montanha, neve).
    Paleta paleta("Cores.txt");
    int totalCores = paleta.obterTamanho(); // Quantidade total de cores disponíveis na paleta

    // NORMALIZAÇÃO DAS ALTITUDES
    // Para colorir o mapa corretamente, precisamos saber qual a menor e a maior altitude gerada.
    double altMin = terreno.altitudes[0][0];
    double altMax = terreno.altitudes[0][0];
    
    // Varre toda a matriz do terreno para encontrar os valores extremos (mínimo e máximo)
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            double alt = terreno.altitudes[i][j];
            if (alt < altMin) altMin = alt;
            if (alt > altMax) altMax = alt;
        }
    }
    // O 'delta' é a amplitude térmica/altimétrica. Se o terreno for totalmente plano, assume 1.0 para evitar divisão por zero.
    double delta = (altMax - altMin == 0) ? 1.0 : (altMax - altMin);

    // CRIAÇÃO DA IMAGEM
    // Cria uma imagem em branco com dimensões correspondentes ao tamanho da matriz do terreno (tam x tam).
    Imagem imagem(tam, tam);

    // CONFIGURAÇÃO DA LUZ PARA O RELEVO (HILLSHADING)
    // O Hillshading simula como a luz solar incide sobre as montanhas para criar sombras realistas (sensação 3D).
    // Vetor de direção da luz (lux, luy, luz). Valores negativos apontam para o canto superior esquerdo (Noroeste).
    double lux = -1.0; 
    double luy = -1.0;
    double luz = 0.4; // Componente Z: quanto menor, mais inclinado/baixo está o sol, gerando sombras mais longas e dramáticas.
    
    // Normalização do vetor de luz: Transforma o vetor em um vetor unitário (comprimento igual a 1),
    // garantindo que os cálculos de produto escalar subsequentes funcionem corretamente.
    double lu_norm = std::sqrt(lux * lux + luy * luy + luz * luz);
    lux /= lu_norm; luy /= lu_norm; luz /= lu_norm;

    // Fator que multiplica as inclinações. Valores maiores tornam as encostas visualmente mais íngremes e escuras.
    double escalaVertical = 30.0; 

    // PROCESSAMENTO E PINTURA DE CADA PIXEL DO MAPA
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            
            // Converte a altitude atual para uma escala entre 0.0 (ponto mais baixo) e 1.0 (ponto mais alto).
            double normalizado = (terreno.altitudes[i][j] - altMin) / delta;
            
            // --- 6.1 SELEÇÃO DA COR BASE ---
            // Mapeia o valor [0.0, 1.0] para um índice inteiro válido na paleta de cores.
            int indiceCor = static_cast<int>(normalizado * (totalCores - 1));
            // Exemplo prático: Se 'totalCores' for 10, os índices vão de 0 a 9.
            // - Ponto mais baixo (normalizado = 0.0): 0.0 * 9 = 0.0 -> índice 0 (Ex: Azul)
            // - Ponto médio     (normalizado = 0.5): 0.5 * 9 = 4.5 -> índice 4 (Ex: Verde)
            // - Ponto mais alto  (normalizado = 1.0): 1.0 * 9 = 9.0 -> índice 9 (Ex: Branco)
            // O '- 1' evita que o código tente acessar um índice inexistente (como o 10), o que travaria o programa.

            // Garante que o índice não saia dos limites do vetor da paleta (evita erros de memória)
            indiceCor = std::clamp(indiceCor, 0, totalCores - 1);

            // Pega a cor correspondente àquela altitude
            Cor corBase = paleta.obterCor(indiceCor);

            // CÁLCULO DAS SOMBRAS (LAMBERTIAN HILLSHADING)
            double dx = 0.0; // Inclinação no eixo X (horizontal)
            double dy = 0.0; // Inclinação no eixo Y (vertical)

            // Diferenças Centrais: Aproxima a inclinação (derivada) do terreno naquele ponto.
            // Olha para o pixel da frente e o de trás. Se a diferença for grande, a encosta é íngreme.
            // Ignora as bordas externas da matriz (i == 0 ou i == tam-1) para não ler memória inválida.
            if (i > 0 && i < tam - 1) dx = (terreno.altitudes[i + 1][j] - terreno.altitudes[i - 1][j]) * escalaVertical;
            if (j > 0 && j < tam - 1) dy = (terreno.altitudes[i][j + 1] - terreno.altitudes[i][j - 1]) * escalaVertical;

            // Define o Vetor Normal da superfície do terreno: N = (-dx, -dy, 1)
            // Este vetor aponta perpendicularmente para fora da montanha.
            double nx = -dx;
            double ny = -dy;
            double nz = 1.0;
            // Normaliza o vetor Normal da superfície para que seu comprimento também seja 1.
            double n_norm = std::sqrt(nx * nx + ny * ny + nz * nz);
            nx /= n_norm; ny /= n_norm; nz /= n_norm;

            // Produto Escalar: Mede o alinhamento entre o vetor da superfície (Normal) e o vetor da Luz.
            // Se estiverem perfeitamente alinhados (face voltada para o sol), o resultado é próximo de 1 (iluminado).
            // Se estiverem opostos (face escondida do sol), o resultado é negativo (sombra).
            double dot = nx * lux + ny * luy + nz * luz;
            
            // Transforma o produto escalar em um multiplicador de iluminação.
            // O intervalo original do 'dot' (-1.0 a 1.0) vira um fator entre 0.6 (sombra) e 1.4 (brilho máximo).
            double fatorIluminacao = 1.0 + (dot * 0.4);

            // TEXTURA DE MICRO-RELEVO (RUÍDO POROSO)
            // Gera um número aleatório pequeno entre -0.07 e +0.07 para simular imperfeições na terra/vegetação.
            double ruidoMicro = ((double)std::rand() / RAND_MAX * 2.0 - 1.0) * 0.07;
            
            // TRATAMENTO DA ÁGUA: Se a altitude estiver abaixo de 0.23 (região considerada oceano/lago):
            if (normalizado < 0.23) { 
                ruidoMicro *= 0.15; // Reduz o ruído drasticamente para a água parecer lisa.
                fatorIluminacao = 1.0 + (dot * 0.08); // Suaviza o efeito das sombras na água
            }

            // Combina o sombreamento tridimensional das encostas com o ruído de textura.
            double fatorFinal = fatorIluminacao + ruidoMicro;

            // APLICAÇÃO DO FATOR NA COR FINAL
            // Multiplica os canais R, G e B originais da paleta pelo fator final de luz e sombra.
            // O 'std::clamp' garante que o resultado fique no intervalo válido de cores para computadores (0 a 255).
            int rFinal = std::clamp(static_cast<int>(corBase.r * fatorFinal), 0, 255);
            int gFinal = std::clamp(static_cast<int>(corBase.g * fatorFinal), 0, 255);
            int bFinal = std::clamp(static_cast<int>(corBase.b * fatorFinal), 0, 255);

            // Aplica a cor final calculada nas coordenadas (i, j) do objeto imagem.
            imagem.setPixel(i, j, Cor(rFinal, gFinal, bFinal));
        }
    }

    // SALVAMENTO DO ARQUIVO
    std::cout << "Salvando " << nomeArquivo << "..." << std::endl;
    imagem.salvarPPM(nomeArquivo);
}

int main() {
    // Semeia o gerador de números aleatórios com 0 
    // Invoca a função
    gerarTerrenoColorido(10, 75.0, "teste_mapa.ppm");
    
    std::cout << "Sucesso! Arquivo 'teste_mapa.ppm' gerado" << std::endl;
    return 0; // Finaliza o programa com sucesso.
}

//g++ main.cpp Terreno.cpp Imagem.cpp Paleta.cpp Cor.cpp -o gerador_terreno && ./gerador_terreno