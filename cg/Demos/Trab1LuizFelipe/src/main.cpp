/***********************************************************************************************
 * Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
 * Autor: Cesar Tadeu Pozzer
 *         05/2024
 *
 *  COMO INTERAGIR:
 *      - Clique no bot�o "Carregar img" para carregar as imagens na tela.
 *      - A �ltima imagem carregada (�ltima posicao do vetor de imagens vai ser a imagem selecionada inicialmente).
 *      - A imagem selecionada possui uma moldura na cor vermelha ao seu redor.
 *      - A imagem selecionada vai ser arrastada dentro do painel onde est�o as imagens, ela n�o sai para fora do painel.
 *      - Para desabilitar o arrasto da imagem selecionada, clique com o bot�o DIREITO do mouse.
 *      - Para selecionar outra imagem � necess�rio inicialmente desabilitar o arrasto da imagem selecionado (mencionado acima)
 *      ent�o, clique na imagem que deseja selecionar;
 *      - Ao clicar no bot�o "Rota��o Vert." a imagem selecionada ter� uma rota��o vertical aplicada a ela.
 *      - Ao clicar no bot�o "Rota��o Horiz." a imagem selecionada ter� uma rota��o horizontal aplicada a ela.
 *      - Ao clicar no bot�o "Canais RGB" a imagem selecionada ser� mostrada em uma escala menor ajustada de acordo com o tamanho
 *      dispon�vel na tela, no canto direito da tela nos 4 canais separados, vermelho, verde, azul e cinza, ou seja 4 imagens
 *      simult�neas, caso seja aplicada alguma rota��o na imagem selecionada, o mesmo ocorrer� com as imagens nos canais separados.
 *      - Ao clicar no bot�o "Histograma" ser� mostrado os 4 histogramas da imagem selecionada ao mesmo tempo no canto direito.
 *      - Caso esteja sendo mostrado os histogramas e seja clicado no bot�o "Canais RGB" as imagens em canais seprados ser�o
 *      mostradas no canto direito, o mesmo � v�lido para a situa��o inversa.
 *      - Ao exibir histogramas ou imagens em canais separados e mudar a imagem selecionada, os histogramas ou as imagens em canais
 *      RGB passar�o a ser da imagem selecionada.
 *      - Para deixar de exibir algo no canto direito, clique no bot�o do que est� aparecendo no momento, ou seja, clique no bot�o
 *      "Histograma" para parar de exibir histogramas ou no bot�o "Canais RGB" para deixar de exibir a imagem em canais separados.
 *
 *
 *  UM POUCO SOBRE O QUE FOU FEITO:
 *
 *  - Foi criada a classe Bmp com inspira��o na classe de mesmo nome da demo Texture, essa classe
 *  permite carregar, processar e exibir imagens no formato BMP.
 *  Ela oferece m�todos para carregar uma imagem BMP de um arquivo, processar cores, calcular e desenhar histogramas,
 *  realizar rota��es na imagem.
 *
 * - A Classe Botao foi aproveitada da demo Canvas_Glut, apenas o Render foi adaptado para ser responsivo com o tamanho da tela;
 *
 * - A classe ManagerBotoes, cria, gerencia e renderiza os botoes na tela, tamb�m trata os cliques nos bot�es e as respectivas a��es
 * ela recebe como par�tro o gerenciador de imagens, pois � ele quem chama as fun��es para operar sobre as imagens, de acordo com
 * os eventos.
 *
 * - A classe ImageManager � responsavel pela instancia��o de imagens, carregamento e exibi��o na tela, o construtor recebe como
 * par�metro um numero de imagens e ent�o esse numero de imagens � carregado, nomeados com a.bmp, b.bmp, c.bmp e assim por diante
 * essa funcao gerencia o clique nas imagens chama as funcoes para renderizar as pr�prias imagens, ela tamb�m desenha os pain�is
 * e define o que pode ou n�o ser mostrados na tela, ela chama funcoes que operam diretamente na classe Bmp.
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
//Deve-se manter essa fun��o com poucas linhas de codigo.
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

    //Se h� imagem selecionada
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
