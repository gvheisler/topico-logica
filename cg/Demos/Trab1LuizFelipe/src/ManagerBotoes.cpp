#include "ManagerBotoes.h"


ManagerBotoes::ManagerBotoes(ImageManager *im)
{
    imageManager = im;
    int widthBotao = screenWidth*0.15;
    int heightBotao = screenHeight*0.07;
    int startY = screenHeight*0.027;
    int startX = screenWidth*0.052;


    // Criação dos botões e adição ao vetor
    botoes.push_back(Botao(startX, startY, widthBotao, heightBotao, "Carregar img"));
    botoes.push_back(Botao(startX + widthBotao + startX/2, startY, widthBotao, heightBotao, "Rotacao Vert."));
    botoes.push_back(Botao(startX + widthBotao*2 + startX/2*2, startY, widthBotao, heightBotao, "Rotacao Horiz."));
    botoes.push_back(Botao(startX + widthBotao*3 + startX/2*3, startY, widthBotao, heightBotao, "Canais RGB"));
    botoes.push_back(Botao(startX + widthBotao*4 + startX/2*4, startY, widthBotao, heightBotao, "Histograma"));
}

ManagerBotoes::~ManagerBotoes()
{
    //dtor
}

void ManagerBotoes::renderizaBotoes() {

    widthBotao = screenWidth * 0.15;
    heightBotao = screenHeight * 0.07;
    startY = screenHeight * 0.027;
    startX = screenWidth * 0.052;

    for (int i = 0; i < (int)botoes.size(); i++) {
        int newStartX = startX + (widthBotao * i) + (startX / 2 * i);
        botoes[i].Render(newStartX,startY,widthBotao,heightBotao);
    }

}

void ManagerBotoes::verificaClique(int mx, int my) {

    for (auto& botao : botoes) {
        if (botao.Colidiu(mx, my)) {
            const char* label = botao.getLabel();
            if (strcmp(label, "Carregar img") == 0) {
                imageManager->carregarImagem();

            } else if (strcmp(label, "Rotacao Vert.") == 0) {
                imageManager->rotacaoVertical();

            } else if (strcmp(label, "Rotacao Horiz.") == 0) {
                imageManager->rotacaoHorizontal();

            } else if (strcmp(label, "Canais RGB") == 0) {
                imageManager->exibirCanaisRGB();

            } else if (strcmp(label, "Histograma") == 0) {
                imageManager->exibirHistograma();

            }
        }
    }

}
