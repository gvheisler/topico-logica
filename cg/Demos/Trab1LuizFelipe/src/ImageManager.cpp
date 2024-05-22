#include "ImageManager.h"
#include "gl_canvas2d.h"


ImageManager::ImageManager(int numImages)
{
    Bmp *bmpi = NULL;
    imagemSelecionada = -1;
    mostrarHistogramas = false;
    mostrarRGB = false;
    mostrarImagem = false;

    //std::string directory = "./1_canvasGlut/images/"; -> LINUX
    std::string directory = ".\\Trab1LuizFelipe\\images\\"; //WINDOWS
    char letter = 'a';
    std::string extension = ".bmp";

    //Agora voltou ao que qera antes
    for (int i = 0; i < numImages; i++) {
        std::string fileName = directory + std::string(1, letter) + extension;
        bmpi = new Bmp(fileName.c_str());

        if(bmpi != NULL) {
            bmpi->startX = bmpi->getWidth()/2;
            bmpi->startY = bmpi->getHeight()/2;
            images.push_back(bmpi);
            bmpi->processaCores();
        }

        letter++;
    }
}

ImageManager::~ImageManager() {
    for (auto bmp : images) {
        delete bmp;
    }
}


bool ImageManager::temImagemselecionada() {
    if (imagemSelecionada != -1) {
        return true;
    } else {
        return false;
    }
}

void ImageManager::Render() {

    //Calcula tamanho do painel
    xStartMainPanel = 1;
    xEndMainPanel = screenWidth*0.68;
    yStartMainPanel = screenHeight/7;
    yEndMainPanel = screenHeight;

    //Desenha Painel das imagens
    CV::color(0.92,0.92,0.95);
    CV::rectFill(xStartMainPanel,yStartMainPanel,xEndMainPanel,yEndMainPanel);
    CV::color(1,0,1);
    CV::rect(xStartMainPanel,yStartMainPanel,xEndMainPanel-1,yEndMainPanel);

    //Desenha imagens
    if(mostrarImagem) {
        for (int i=0; i < (int)images.size(); i++) {
            images[i]->Render(images[i]->startX,images[i]->startY);
        }

        //desenha moldura
        CV::color(1,0,0);
        int startX = images[imagemSelecionada]->startX;
        int startY = images[imagemSelecionada]->startY;
        int largura = startX + images[imagemSelecionada]->getWidth();
        int altura = startY + images[imagemSelecionada]->getHeight();

        CV::rect(startX-1,startY-1,largura+1,altura+1);
        CV::rect(startX-2,startY-2,largura+2,altura+2);
    }

    //Desenha painel do lado direito
    CV::color(1,1,1);
    CV::rectFill(screenWidth*0.68,screenHeight/7,screenWidth,screenHeight);
    CV::color(1,0,1);
    CV::rect(screenWidth*0.68,screenHeight/7,screenWidth,screenHeight);

    //desenha histogramas
    if(mostrarHistogramas) {
        //posicoes aleatorias
        images[imagemSelecionada]->desenhaHistograma(images[imagemSelecionada]->histogramaRed,images[imagemSelecionada]->RED,screenWidth*0.73,screenHeight*0.35);
        images[imagemSelecionada]->desenhaHistograma(images[imagemSelecionada]->histogramaGreen,images[imagemSelecionada]->GREEN,screenWidth*0.73,screenHeight*0.55);
        images[imagemSelecionada]->desenhaHistograma(images[imagemSelecionada]->histogramaBlue,images[imagemSelecionada]->BLUE,screenWidth*0.73,screenHeight*0.75);
        images[imagemSelecionada]->desenhaHistograma(images[imagemSelecionada]->histogramaGray,images[imagemSelecionada]->GRAY,screenWidth*0.73,screenHeight*0.95);
    }

    //desenha Imagens em canais separados
    if(mostrarRGB) {
        images[imagemSelecionada]->desenhaRGB();
    }

}

void ImageManager::carregarImagem() {
        mostrarImagem = true;
        imagemSelecionada = (int)images.size() - 1;
}


void ImageManager::verificaClique(int mx, int my) {
    for (int i = (int)images.size() - 1; i >=0; i--) {

            if (mx >= images[i]->startX && mx <= images[i]->startX + images[i]->getWidth() &&
                my >= images[i]->startY && my <= images[i]->startY + images[i]->getHeight()) {

                std::swap(images[i], images[(int)images.size() - 1]);
                imagemSelecionada = (int)images.size() - 1; // Definir a imagem clicada como selecionada

                //guardar posicao da imagem que foi clicada
                click_x = mx - images[imagemSelecionada]->startX;
                click_y = my - images[imagemSelecionada]->startY;

                break; // Parar de percorrer as imagens após encontrar a primeira clicada
            }
        }
}

void ImageManager::Motion(int x, int y) {
    int newXstart = x - click_x;
    int newYstart = y - click_y;
    int newXEnd = newXstart + images[imagemSelecionada]->getWidth();
    int newYEnd = newYstart + images[imagemSelecionada]->getHeight();

    if(xStartMainPanel <= newXstart && newXEnd <= xEndMainPanel && yStartMainPanel <= y && x <= xEndMainPanel) {
        images[imagemSelecionada]->startX = x - click_x;
    }

    if(yStartMainPanel <= newYstart && newYEnd <= yEndMainPanel && yStartMainPanel <= y && x <= xEndMainPanel) {
        images[imagemSelecionada]->startY = y - click_y;
    }
}

void ImageManager::rotacaoVertical(){
    if (imagemSelecionada >= 0 && imagemSelecionada < (int)images.size()) {
        images[imagemSelecionada]->rotacaoVertical();

    }
}

void ImageManager::rotacaoHorizontal(){
    if (imagemSelecionada >= 0 && imagemSelecionada < (int)images.size()) {
        images[imagemSelecionada]->rotacaoHorizontal();

    }
}

void ImageManager::exibirHistograma() {
    if (imagemSelecionada >= 0 && imagemSelecionada < (int)images.size()) {
        if(mostrarRGB == true) {
            mostrarRGB = false;
        }

        if(mostrarHistogramas == false) {
            mostrarHistogramas = true;
        } else {
            mostrarHistogramas = false;
        }
    }
}

void ImageManager::exibirCanaisRGB() {
    if (imagemSelecionada >= 0 && imagemSelecionada < (int)images.size()) {
        if(mostrarHistogramas == true) {
            mostrarHistogramas = false;
        }

        if(mostrarRGB == false) {
            mostrarRGB = true;
        } else {
            mostrarRGB = false;
        }
    }
}
