/***********************************************************************************************
 * Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
 * Autor: Cesar Tadeu Pozzer
 *         05/2024
 *
 *  COMO INTERAGIR:
 *      - Clique no botão "Carregar img" para carregar as imagens na tela.
 *      - A última imagem carregada (última posicao do vetor de imagens vai ser a imagem selecionada inicialmente).
 *      - A imagem selecionada possui uma moldura na cor vermelha ao seu redor.
 *      - A imagem selecionada vai ser arrastada dentro do painel onde estão as imagens, ela não sai para fora do painel.
 *      - Para desabilitar o arrasto da imagem selecionada, clique com o botão DIREITO do mouse.
 *      - Para selecionar outra imagem é necessário inicialmente desabilitar o arrasto da imagem selecionado (mencionado acima)
 *      então, clique na imagem que deseja selecionar;
 *      - Ao clicar no botão "Rotação Vert." a imagem selecionada terá uma rotação vertical aplicada a ela.
 *      - Ao clicar no botão "Rotação Horiz." a imagem selecionada terá uma rotação horizontal aplicada a ela.
 *      - Ao clicar no botão "Canais RGB" a imagem selecionada será mostrada em uma escala menor ajustada de acordo com o tamanho
 *      disponível na tela, no canto direito da tela nos 4 canais separados, vermelho, verde, azul e cinza, ou seja 4 imagens
 *      simultâneas, caso seja aplicada alguma rotação na imagem selecionada, o mesmo ocorrerá com as imagens nos canais separados.
 *      - Ao clicar no botão "Histograma" será mostrado os 4 histogramas da imagem selecionada ao mesmo tempo no canto direito.
 *      - Caso esteja sendo mostrado os histogramas e seja clicado no botão "Canais RGB" as imagens em canais seprados serão
 *      mostradas no canto direito, o mesmo é válido para a situação inversa.
 *      - Ao exibir histogramas ou imagens em canais separados e mudar a imagem selecionada, os histogramas ou as imagens em canais
 *      RGB passarão a ser da imagem selecionada.
 *      - Para deixar de exibir algo no canto direito, clique no botão do que está aparecendo no momento, ou seja, clique no botão
 *      "Histograma" para parar de exibir histogramas ou no botão "Canais RGB" para deixar de exibir a imagem em canais separados.
 *
 *
 *  UM POUCO SOBRE O QUE FOU FEITO:
 *
 *  - Foi criada a classe Bmp com inspiração na classe de mesmo nome da demo Texture, essa classe
 *  permite carregar, processar e exibir imagens no formato BMP.
 *  Ela oferece métodos para carregar uma imagem BMP de um arquivo, processar cores, calcular e desenhar histogramas,
 *  realizar rotações na imagem.
 *
 * - A Classe Botao foi aproveitada da demo Canvas_Glut, apenas o Render foi adaptado para ser responsivo com o tamanho da tela;
 *
 * - A classe ManagerBotoes, cria, gerencia e renderiza os botoes na tela, também trata os cliques nos botões e as respectivas ações
 * ela recebe como parêtro o gerenciador de imagens, pois é ele quem chama as funções para operar sobre as imagens, de acordo com
 * os eventos.
 *
 * - A classe ImageManager é responsavel pela instanciação de imagens, carregamento e exibição na tela, o construtor recebe como
 * parâmetro um numero de imagens e então esse numero de imagens é carregado, nomeados com a.bmp, b.bmp, c.bmp e assim por diante
 * essa funcao gerencia o clique nas imagens chama as funcoes para renderizar as próprias imagens, ela também desenha os painéis
 * e define o que pode ou não ser mostrados na tela, ela chama funcoes que operam diretamente na classe Bmp.
 *
 * - Y cresce para baixo
 *
 ***********************************************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gl_canvas2d.h"

#include "ManagerBotoes.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela
int screenWidth = 960;
int screenHeight = 720;
bool podeMoverImagem = false;

ManagerBotoes   *mbt = NULL; //ponteiro Manager Botoes
ImageManager *im = NULL; //ponteiro Manager de Imagens

int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    CV::clear(1,1,1);

    mbt->renderizaBotoes();
    im->Render();
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if(button == 0) {
        if( state == 0 ) //clicou
        {
            podeMoverImagem = true;

            im->verificaClique(x,y);
            mbt->verificaClique(x,y);

        }
    } else if (button == 2) {
        podeMoverImagem = false;
    }

    //Se há imagem selecionada
    if (im->temImagemselecionada() && state < 0 && podeMoverImagem){
        im->Motion(mouseX,mouseY);
    }

}


int main(void)
{
    int numImagem = 3; //Numero de imagens
    im = new ImageManager(numImagem);
    mbt = new ManagerBotoes(im);

    CV::init(screenWidth, screenHeight, "T1 - CG: Luiz Felipe Cavalheiro");
    CV::run();

    delete mbt;
    delete im;

}
